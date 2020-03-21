import asyncio
import os
import time
from dataclasses import dataclass

import requests_unixsocket
from aiohttp import ClientSession, web


@dataclass(frozen=True)
class Replica:
    replica_id: str
    ip: str
    is_self: bool


def replicas_discovery():
    session = requests_unixsocket.Session()
    number_of_replicas = int(os.environ['REPLICAS'])
    app_codename = os.environ['APP_CODENAME']
    self_hostname = os.environ['HOSTNAME']

    registered_replicas = set()
    while len(registered_replicas) < number_of_replicas:
        cluster_config = session.get('http+unix://%2Fvar%2Frun%2Fdocker.sock/v1.24/containers/json').json()
        replicas = {
            Replica(
                replica_id=x['Id'],
                ip=x['NetworkSettings']['Networks']['register_default']['IPAddress'],
                is_self=x['Id'].startswith(self_hostname)
            )
            for x in cluster_config
            if app_codename in x['Labels']
        }
        registered_replicas.update(replicas)

        if len(registered_replicas) < number_of_replicas:
            time.sleep(2)

    return registered_replicas


replicas = replicas_discovery()
self_id = next(filter(lambda x: x.is_self, replicas)).replica_id


async def index(request):
    for replica in replicas:
        async with ClientSession() as session:
            async with session.get("http://{}:8080/hello".format(replica.ip), headers={'ReplicaId': self_id}) as r:
                await r.text()
    return web.Response(text='ok')
                # print(r.headers['ReplicaId'], flush=True)


async def hello(request):
    requested_id = request.headers['ReplicaId']
    print("Hello from {}".format(requested_id), flush=True)
    return web.Response(text='ok')

print(replicas, flush=True)

app = web.Application()
app.add_routes([web.get('/', index),
                web.get('/hello', hello)])

web.run_app(app, host='0.0.0.0', port=8080)

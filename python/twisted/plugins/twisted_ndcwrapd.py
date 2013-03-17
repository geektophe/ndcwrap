#!/usr/bin/env python

from zope.interface import implements

from twisted.python import usage
from twisted.plugin import IPlugin
from twisted.application.service import IServiceMaker
from twisted.application import internet
from twisted.web import resource, server


SERVICES_FILE = "/var/lib/ndcwrap/services.thr"


class ServicesDefinitionRebader(resource.Resource):
    isLeaf = True

    def render_GET(self, request):
        fp = open(SERVICES_FILE)
        services = fp.read()
        fp.close()
        request.setHeader("Content-Type", "text/plain")
        return services


class Options(usage.Options):
    optParameters = [["port", "p", 8080, "The port number to listen on.", int]]


class ServiceMaker(object):
    implements(IServiceMaker, IPlugin)
    tapname = "ndcwrapd"
    description = "Manipulates ndcwrap services definition file."
    options = Options

    def makeService(self, options):
        """
        Construct a TCPServer from a factory defined in myproject.
        """
        site = server.Site(ServicesDefinitionRebader())
        return internet.TCPServer(options["port"], site)


serviceMaker = ServiceMaker()

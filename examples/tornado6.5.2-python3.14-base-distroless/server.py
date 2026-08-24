import asyncio
import tornado

PORT = 8080

class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.write("Bye, World!\n")

def make_app():
    return tornado.web.Application([
        (r"/", MainHandler),
    ])

async def main():
    app = make_app()
    app.listen(PORT)
    print("Server is listening on port {}".format(PORT))
    await asyncio.Event().wait()

if __name__ == "__main__":
    asyncio.run(main())

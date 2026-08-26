import django
from django.conf import settings
from django.http import HttpResponse
from django.urls import path

settings.configure(
    ROOT_URLCONF=__name__,
    ALLOWED_HOSTS=["*"],
    SECRET_KEY="s3cr3t",
)
django.setup()


def hello(request):
    return HttpResponse("Bye, World!\n")


urlpatterns = [
    path("", hello),
]

if __name__ == "__main__":
    from django.core.management import execute_from_command_line
    execute_from_command_line(["", "runserver", "0.0.0.0:8080", "--noreload"])
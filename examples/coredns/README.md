## Run and Use

Use `kraft` to run the image and start a Unikraft instance:

```bash
kraft net create kraft0
kraft run --network kraft0 -M 512Mi -v ./conf/:/conf/
```

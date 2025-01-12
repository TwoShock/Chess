# Run Game

Run the docker build command:
```
docker build -t chess .
```

To run tests:
```
docker run chess
```

To run the game:
```
docker run -it -e RUN_TESTS=false chess 
```
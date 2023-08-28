xhost local:root


XAUTH=/tmp/.docker.xauth
docker rm test

docker run -it \
    --name=test \
    --env="DISPLAY=$DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --env="XAUTHORITY=$XAUTH" \
    --volume="$XAUTH:$XAUTH" \
    --net=host \
    --privileged \
    -v ~/BT/:/BT/ \
    ubuntu:20.04 \
    bash

echo "Done."

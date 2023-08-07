
xhost local:root


XAUTH=/tmp/.docker.xauth


docker run -it \
    --name=ros2_foxy_cont \
    --env="DISPLAY=$DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --env="XAUTHORITY=$XAUTH" \
    --volume="$XAUTH:$XAUTH" \
    --net=host \
    --privileged \
    -v ~/ros2_ws/:/arche_ws/ \
    archerobotic/arche:ros2-foxy-desktop-full-v0.8 \
    bash

echo "Done."

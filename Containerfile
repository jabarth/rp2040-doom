# Use a suitable base image
FROM ubuntu:latest

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary build tools
RUN apt-get update && apt-get install -y \
    cmake \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    git \
    build-essential \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Clone Pico-SDK
WORKDIR /opt
RUN git clone --recursive https://github.com/raspberrypi/pico-sdk.git
ENV PICO_SDK_PATH=/opt/pico-sdk

# Clone Pico-Extras
WORKDIR /opt
RUN git clone --recursive https://github.com/raspberrypi/pico-extras.git
ENV PICO_EXTRAS_PATH=/opt/pico-extras

# Copy the custom board header into the SDK's board directory
# The file is pico_game_hat_ep0172.h and the board name will be PICO_GAME_HAT_EP0172
# The SDK expects the file to be named after the board name in uppercase, e.g., PICO_GAME_HAT_EP0172.h
COPY pico_game_hat_ep0172.h /opt/pico-sdk/src/boards/include/boards/PICO_GAME_HAT_EP0172.h

# Copy the local patch file to fix compilation and linking errors
COPY pico_doom_fixes_v5.patch /pico_doom_fixes_v5.patch

# Clone the project source (rp2040-doom) into the container
WORKDIR /app
RUN git clone --recursive https://github.com/kilograham/rp2040-doom.git .
# Apply local patches to fix compilation and linking errors
RUN patch -p1 < /pico_doom_fixes_v5.patch

# Create build directory and build the project
WORKDIR /app/build
RUN cmake -DPICO_BOARD=PICO_GAME_HAT_EP0172 -DPICO_SDK_PATH=/opt/pico-sdk -DPICO_OPTIMIZED_DEBUG=1 -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug .. && \
    make -j$(nproc)

# Optionally, specify the default command to run when the container starts
# CMD ["bash"]

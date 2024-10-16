# Use a base image with a suitable version of Ubuntu
FROM ubuntu:22.04

# Set environment variables for non-interactive apt installation
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages for apt, curl, gnupg, Python3, NumPy, Nano, and Git
RUN apt-get update && \
    apt-get install -y apt-transport-https curl gnupg python3 python3-numpy nano git && \
    curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel-archive-keyring.gpg && \
    mv bazel-archive-keyring.gpg /usr/share/keyrings && \
    echo "deb [arch=amd64 signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8" > /etc/apt/sources.list.d/bazel.list && \
    apt-get update && \
    apt-get install -y bazel && \
    apt-get install -y openjdk-11-jdk && \
    apt-get install -y libc6 libncurses5-dev libstdc++6 lib32z1 libbz2-1.0 && \
    apt-get update && apt-get full-upgrade -y && \
    apt-get install -y bazel-5.3.2 && \
    apt-get clean && rm -rf /var/lib/apt/lists/* 

# Create a non-root user
RUN useradd -m -s /bin/bash user

# Give the new user sudo privileges (optional)
RUN echo "user ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

# Switch to the new user
USER user

# Set the default working directory
WORKDIR /home/user

# Clone the specified Git repository and check out the desired branch
# RUN git clone https://github.com/vdepedraza/lyra.git /home/user/lyra && \
    # cd /home/user/lyra && \
    # git checkout fix-build

# Start the container with a bash shell
CMD ["/bin/bash"]
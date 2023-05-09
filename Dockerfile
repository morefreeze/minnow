FROM silkeh/clang:15
RUN mkdir /data
WORKDIR /data
RUN apt -qq update && \
    apt install -qqy --no-install-recommends  fzf git lldb-15
RUN wget https://github.com/Kitware/CMake/releases/download/v3.24.2/cmake-3.24.2-linux-x86_64.sh && \
    chmod u+x cmake-3.24.2-linux-x86_64.sh
RUN mkdir -p /usr/lib/lib/python3.9/ && ln -s /usr/lib/llvm-15/lib/python3.9/site-packages/ /usr/lib/lib/python3.9/site-packages
COPY ./services /etc/services
VOLUME [ "/data" ]
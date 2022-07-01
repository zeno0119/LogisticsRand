FROM ubuntu:20.04
ENV DEBIAN_FRONTEND noninteractive
RUN apt update && apt install -y gcc cmake git
CMD ["sh", "-c", "tail -f /dev/null"]
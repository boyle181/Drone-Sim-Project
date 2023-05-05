FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
  build-essential \  
  libssl-dev \
  zlib1g-dev

# 1 - make directory to run container
RUN mkdir /app

# 2 - copy project into newly created directory
COPY . app/

# 3 - CD into new directory for running container
WORKDIR /app

# 4 - compile code
RUN make -j

# 5 - run command in docker container once image ran
CMD ["./build/bin/transit_service", "8091", "apps/transit_service/web/"]
# ./build/bin/transit_service 8091 apps/transit_service/web/
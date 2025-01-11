FROM alpine:latest

# Install build dependencies
RUN apk add --no-cache \
    build-base \
    cmake \
    git

# Set the working directory
WORKDIR /app

# Copy project files
COPY . /app

# Create build directory, configure, and build
RUN mkdir build
WORKDIR /app/build
RUN cmake .. && cmake --build .

# Run tests
CMD ["./ChessTest"]

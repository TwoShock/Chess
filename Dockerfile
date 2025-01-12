FROM alpine:latest

# Install build dependencies
RUN apk add --no-cache \
    build-base \
    cmake \
    git \
    dos2unix

# Set the working directory
WORKDIR /app

# Copy project files
COPY . /app

# Normalize line endings to Unix-style (\n) for all text files
RUN find /app -type f -exec dos2unix {} \;

# Create build directory, configure, and build
RUN mkdir build
WORKDIR /app/build
RUN cmake .. && cmake --build .

ENV RUN_TESTS=true
# Run tests
# Fixed CMD instruction with proper syntax
CMD if [ "${RUN_TESTS}" = "true" ]; then \
        ./ChessTest; \
    else \
        ./ChessGame; \
    fi

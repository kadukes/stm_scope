#!/bin/bash

# STM32F429I Remote Debug Script
# This script starts OpenOCD and launches GDB for debugging
set -e

# Configuration
OPENOCD_CONFIG="debug/openocd.cfg"
GDB_INIT="debug/gdbinit"
ELF_FILE="build/stm_scope.elf"
OPENOCD_PORT=3333
OPENOCD_PID_FILE="/tmp/openocd_stm32.pid"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Function to print colored messages
print_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to cleanup on exit
cleanup() {    
    print_info "Cleaning up..."
    if [ -f "$OPENOCD_PID_FILE" ]; then
        local pid=$(cat "$OPENOCD_PID_FILE")
        if kill -0 "$pid" 2>/dev/null; then
            print_info "Stopping OpenOCD (PID: $pid)..."
            kill "$pid" 2>/dev/null || true
            sleep 1
        fi
        rm -f "$OPENOCD_PID_FILE"
    fi
}

# Set up signal handlers
trap cleanup EXIT INT TERM

# Find available GDB
GDB_COMMAND="gdb-multiarch"

# Start OpenOCD
print_info "Starting OpenOCD..."
openocd -f "$OPENOCD_CONFIG" &
OPENOCD_PID=$!
echo $OPENOCD_PID > "$OPENOCD_PID_FILE"
    
# Wait for OpenOCD to start
print_info "Waiting for OpenOCD to start..."
for i in {1..10}; do
    if ss -tuln 2>/dev/null | grep -q ":$OPENOCD_PORT "; then
        print_info "OpenOCD started successfully"
        break
    fi
    if [ $i -eq 10 ]; then
        print_error "OpenOCD failed to start"
        exit 1
    fi
    sleep 1
done

# Use the found GDB with the initialization script
if $GDB_COMMAND \
    -x "$GDB_INIT" \
    "$ELF_FILE"; then
    print_info "Debug session ended normally"
    cleanup
    exit 0
else
    print_error "GDB session failed with exit code $?"
    cleanup
    exit 1
fi

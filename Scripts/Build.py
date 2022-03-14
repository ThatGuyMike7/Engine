import argparse
import platform
import sys
import subprocess
import os

SystemName = platform.system()
if (SystemName != "Windows" and SystemName != "Linux" and SystemName != "Darwin"):
    print("Error: Unknown Host Operating System \"" + SystemName + "\".")
    sys.exit(1)

parser = argparse.ArgumentParser("Build")
parser.add_argument("Arch", choices = ["x64", "ARM64"], help = "Target architecture, must match architecture of host machine.")
parser.add_argument("BuildType", choices = ["Debug", "Release", "RelWithDebInfo", "MinSizeRel"], help = "Build type.")
args = parser.parse_args()

CMakeSourceDir = "."
CMakeBuildDir = os.path.join(".", "Build", SystemName, args.Arch, args.BuildType)

# We specify both `CMAKE_BUILD_TYPE` for single-configuration generators (Make, Ninja, ...)
# and `--config` for multi-configuration generators (Visual Studio, ...).
# Not sure if it's required to specify both but we just do it.
CMakeGenerateCommand = "cmake -S\"" + CMakeSourceDir + "\" -B\"" + CMakeBuildDir + "\" -DARCH=" + args.Arch + " -DBUILD_TYPE=" + args.BuildType + " -DCMAKE_BUILD_TYPE=" + args.BuildType
CMakeBuildCommand = "cmake --build \"" + CMakeBuildDir + "\" --config " + args.BuildType

print("Host Operating System: \"" + SystemName + "\"")
print("Arichtecture: \"" + args.Arch + "\"")
print("CMake Build Directory: \"" + CMakeBuildDir + "\"")
print("CMake Generate Command: \"" + CMakeGenerateCommand + "\"")
print("CMake Build Command: \"" + CMakeBuildCommand + "\"")

print("Calling CMake (Generate)...")
subprocess.run(CMakeGenerateCommand, shell = True)

print("Calling CMake (Build)...")
subprocess.run(CMakeBuildCommand, shell = True)
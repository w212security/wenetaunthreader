#!/usr/bin/python3
import sys

print("[*] create_bundle_patches at your service.")

if len(sys.argv) != 2:
    print("USAGE: " + sys.argv[0] +  " {BUNDLEID}")
    sys.exit(0)
bundleId = sys.argv[1]

enablepatch = open("/unthreader/patches/enable", "w")
enablepatch.write("""{
  "ActiveAppSelfLocked" : false,
  "ActiveAppID" : "%s",
  "SelfLockUnmanaged" : false
}""" % sys.argv[1])
enablepatch.close()
disablepatch = open("/unthreader/patches/disable", "w")
disablepatch.write("""{
  "ActiveAppSelfLocked" : false,
  "SelfLockUnmanaged" : false
}""")
disablepatch.close()

print("[*] done")
#!/usr/bin/env bash
# Bundle build/bin/otto into dist/OTTO.app for Finder launch.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
BIN="$ROOT/build/bin/otto"
APP="$ROOT/dist/OTTO.app"
CONTENTS="$APP/Contents"
MACOS="$CONTENTS/MacOS"
RES="$CONTENTS/Resources"

if [[ ! -x "$BIN" ]]; then
  echo "Missing $BIN — run: just build otto_exec" >&2
  exit 1
fi

rm -rf "$APP"
mkdir -p "$MACOS" "$RES"

cp "$BIN" "$MACOS/OTTO"
chmod +x "$MACOS/OTTO"
cp -R "$ROOT/resources" "$RES/resources"
cp -R "$ROOT/data" "$RES/data"
if [[ -f "$ROOT/ottoconf.mac.json" ]]; then
  cp "$ROOT/ottoconf.mac.json" "$RES/ottoconf.json"
fi

# Launcher sets cwd to Resources so ./data and ./resources resolve.
cat > "$MACOS/otto-launch" <<'EOF'
#!/bin/bash
DIR="$(cd "$(dirname "$0")" && pwd)"
RES="$(cd "$DIR/../Resources" && pwd)"
cd "$RES"
exec "$DIR/OTTO" -e -d "$RES/data" -r "$RES/resources" -c "$RES/ottoconf.json" "$@"
EOF
chmod +x "$MACOS/otto-launch"

# App icon: cyan ring on dark navy → AppIcon.icns
ICONSET="$RES/AppIcon.iconset"
mkdir -p "$ICONSET"
python3 - "$ICONSET" <<'PY'
import struct, sys, zlib
from pathlib import Path

def png(w, h, rgba_fn):
    def chunk(tag, data):
        return struct.pack(">I", len(data)) + tag + data + struct.pack(">I", zlib.crc32(tag + data) & 0xFFFFFFFF)
    rows = []
    for y in range(h):
        row = bytearray([0])
        for x in range(w):
            row.extend(rgba_fn(x, y))
        rows.append(bytes(row))
    raw = b"".join(rows)
    return (
        b"\x89PNG\r\n\x1a\n"
        + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 6, 0, 0, 0))
        + chunk(b"IDAT", zlib.compress(raw, 9))
        + chunk(b"IEND", b"")
    )

def color(x, y, s):
    cx, cy, r = s / 2, s / 2, s * 0.38
    d2 = (x - cx) ** 2 + (y - cy) ** 2
    if d2 <= (r * 0.55) ** 2:
        return (20, 24, 40, 255)
    if d2 <= r * r:
        return (0, 200, 220, 255)
    return (18, 22, 36, 255)

iconset = Path(sys.argv[1])
mapping = {
    16: ["icon_16x16.png"],
    32: ["icon_16x16@2x.png", "icon_32x32.png"],
    64: ["icon_32x32@2x.png"],
    128: ["icon_128x128.png"],
    256: ["icon_128x128@2x.png", "icon_256x256.png"],
    512: ["icon_256x256@2x.png", "icon_512x512.png"],
    1024: ["icon_512x512@2x.png"],
}
for size, names in mapping.items():
    data = png(size, size, lambda x, y, s=size: color(x, y, s))
    for name in names:
        (iconset / name).write_bytes(data)
PY
iconutil -c icns "$ICONSET" -o "$RES/AppIcon.icns"
rm -rf "$ICONSET"

cat > "$CONTENTS/Info.plist" <<'EOF'
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>CFBundleName</key>
  <string>OTTO</string>
  <key>CFBundleDisplayName</key>
  <string>OTTO</string>
  <key>CFBundleIdentifier</key>
  <string>com.bitfieldaudio.otto.desktop</string>
  <key>CFBundleVersion</key>
  <string>0.0.2</string>
  <key>CFBundleShortVersionString</key>
  <string>0.0.2</string>
  <key>CFBundleExecutable</key>
  <string>otto-launch</string>
  <key>CFBundlePackageType</key>
  <string>APPL</string>
  <key>CFBundleIconFile</key>
  <string>AppIcon</string>
  <key>LSMinimumSystemVersion</key>
  <string>12.0</string>
  <key>NSHighResolutionCapable</key>
  <true/>
  <key>NSMicrophoneUsageDescription</key>
  <string>OTTO uses audio input when a duplex device is selected.</string>
</dict>
</plist>
EOF

echo "Built $APP"
echo "Open with: open \"$APP\""

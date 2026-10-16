package main

import (
	"context"
	"log"
	"os"
	"path/filepath"
	"runtime"
	"strings"

	"github.com/tetratelabs/wazero"
	"github.com/tetratelabs/wazero/imports/wasi_snapshot_preview1"
)

func main() {
	runtime.GOMAXPROCS(4)
	ctx := context.Background()

	r := wazero.NewRuntime(ctx)
	defer r.Close(ctx)

	wasi_snapshot_preview1.MustInstantiate(ctx, r)

	payloadDir := "/app/payloads"
	files, err := os.ReadDir(payloadDir)
	if err != nil {
		log.Fatalf("Failed to read payloads directory: %v", err)
	}

	for _, file := range files {
		if strings.HasSuffix(file.Name(), ".wasm") {
			wasmBytes, err := os.ReadFile(filepath.Join(payloadDir, file.Name()))
			if err != nil {
				log.Printf("Failed to read %s: %v", file.Name(), err)
				continue
			}

			config := wazero.NewModuleConfig().
				WithStdout(os.Stdout).
				WithStderr(os.Stderr)

			_, err = r.InstantiateWithConfig(ctx, wasmBytes, config)
			if err != nil {
				log.Printf("Failed to execute %s: %v", file.Name(), err)
			}
		}
	}
}


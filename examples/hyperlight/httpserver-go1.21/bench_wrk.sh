#!/usr/bin/env bash
# wrk load test for the Go HTTP server on Hyperlight.
# Server must already be running (just run).

set -euo pipefail

BASE_URL="${BASE_URL:-http://127.0.0.1:8080}"
WRK_THREADS="${WRK_THREADS:-4}"
WRK_CONNECTIONS="${WRK_CONNECTIONS:-64}"
WRK_DURATION="${WRK_DURATION:-30s}"
WRK_BODY="${WRK_BODY:-hello from wrk}"

log() {
    printf '[%s] %s\n' "$(date '+%Y-%m-%d %H:%M:%S')" "$*"
}

fail() {
    log "ERROR: $*"
    exit 1
}

command -v wrk >/dev/null 2>&1 || fail "missing required command: wrk"

run_wrk_get() {
    log "wrk: GET ${BASE_URL}/"
    log "  threads=${WRK_THREADS}  connections=${WRK_CONNECTIONS}  duration=${WRK_DURATION}"
    wrk -t"${WRK_THREADS}" -c"${WRK_CONNECTIONS}" -d"${WRK_DURATION}" "${BASE_URL}/"
}

run_wrk_post() {
    local script_file
    script_file="$(mktemp)"
    cat > "${script_file}" <<EOF
wrk.method = "POST"
wrk.body = "${WRK_BODY}"
wrk.headers["Content-Type"] = "text/plain"
EOF

    log "wrk: POST ${BASE_URL}/wrk"
    log "  threads=${WRK_THREADS}  connections=${WRK_CONNECTIONS}  duration=${WRK_DURATION}"
    log "  body=\"${WRK_BODY}\" (${#WRK_BODY} bytes)"
    wrk -t"${WRK_THREADS}" -c"${WRK_CONNECTIONS}" -d"${WRK_DURATION}" -s "${script_file}" "${BASE_URL}/wrk"
    rm -f "${script_file}"
}

main() {
    log "wrk load test against ${BASE_URL}"
    echo

    log "=== GET / ==="
    run_wrk_get
    echo

    log "=== POST /wrk ==="
    run_wrk_post
    echo

    log "Done"
}

main "$@"

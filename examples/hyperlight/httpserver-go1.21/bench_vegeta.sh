#!/usr/bin/env bash
# vegeta load test for the Go HTTP server on Hyperlight.
# Server must already be running (just run).

set -euo pipefail

BASE_URL="${BASE_URL:-http://127.0.0.1:8080}"
VEGETA_RATE="${VEGETA_RATE:-100}"
VEGETA_DURATION="${VEGETA_DURATION:-10s}"
VEGETA_WORKERS="${VEGETA_WORKERS:-4}"
POST_BODY="${POST_BODY:-hello from vegeta}"

log() {
    printf '[%s] %s\n' "$(date '+%Y-%m-%d %H:%M:%S')" "$*"
}

fail() {
    log "ERROR: $*"
    exit 1
}

command -v vegeta >/dev/null 2>&1 || fail "missing required command: vegeta (go install github.com/tsenart/vegeta/v12@latest)"

run_vegeta_get() {
    log "vegeta: GET ${BASE_URL}/"
    log "  rate=${VEGETA_RATE}/s  duration=${VEGETA_DURATION}  workers=${VEGETA_WORKERS}"

    echo "GET ${BASE_URL}/" \
        | vegeta attack \
            -rate "${VEGETA_RATE}" \
            -duration "${VEGETA_DURATION}" \
            -workers "${VEGETA_WORKERS}" \
        | vegeta report
}

run_vegeta_post() {
    local body_file
    body_file="$(mktemp)"
    printf '%s' "${POST_BODY}" > "${body_file}"

    log "vegeta: POST ${BASE_URL}/wrk"
    log "  rate=${VEGETA_RATE}/s  duration=${VEGETA_DURATION}  workers=${VEGETA_WORKERS}"
    log "  body=\"${POST_BODY}\" (${#POST_BODY} bytes)"

    printf 'POST %s/wrk\nContent-Type: text/plain\n@%s\n' "${BASE_URL}" "${body_file}" \
        | vegeta attack \
            -rate "${VEGETA_RATE}" \
            -duration "${VEGETA_DURATION}" \
            -workers "${VEGETA_WORKERS}" \
        | vegeta report

    rm -f "${body_file}"
}

main() {
    log "vegeta load test against ${BASE_URL}"
    echo

    log "=== GET / ==="
    run_vegeta_get
    echo

    log "=== POST /wrk ==="
    run_vegeta_post
    echo

    log "Done"
}

main "$@"

#!/bin/bash

SCRIPT_DIR=$(dirname $0)

mv ${SCRIPT_DIR}/.libs/*.gcno ${SCRIPT_DIR}
mv ${SCRIPT_DIR}/.libs/*.gcda ${SCRIPT_DIR}

lcov -d src --base-directory src/libsort --capture --output-file coverage.info
genhtml coverage.info -o ./coverage
firefox ./coverage/index.html

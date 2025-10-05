#!/bin/bash

# Цвета
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

counter=1

# Заголовок таблицы
printf "%-50s %-15s %-15s\n" "MAP" "VALIDATION" "MEMORY"
printf "%-50s %-15s %-15s\n" "---" "----------" "------"

for map in maps/bad/*.cub; do
  # Проверка без valgrind на наличие Error
  APP_OUTPUT=$(./app "$map" 2>&1)
  
  if echo "$APP_OUTPUT" | grep -qi "error"; then
    VALIDATION="${RED}ERROR${NC}"
    MEMORY="-"
  else
    VALIDATION="${GREEN}OK${NC}"
    
    # Проверка утечек памяти с valgrind
    VALGRIND_OUTPUT=$(valgrind --leak-check=full --show-leak-kinds=all ./app "$map" 2>&1)
    
    if echo "$VALGRIND_OUTPUT" | grep -q "no leaks are possible" && \
       ! echo "$VALGRIND_OUTPUT" | grep -q "ERROR SUMMARY: [1-9]"; then
      MEMORY="${GREEN}OK${NC}"
    else
      MEMORY="${RED}LEAK${NC}"
    fi
  fi
  
  printf "%-50s %-25s %-25s\n" "$counter. $map" "$(echo -e "$VALIDATION")" "$(echo -e "$MEMORY")"
  ((counter++))
done

#!/bin/bash
# 테스트 스크립트

echo "베셀 함수 근 찾기 테스트 시작..."

# 컴파일 테스트
echo "1. 컴파일 테스트..."
make clean > /dev/null 2>&1
if make > /dev/null 2>&1; then
    echo "   ✓ 컴파일 성공"
else
    echo "   ✗ 컴파일 실패"
    exit 1
fi

# 실행 테스트  
echo "2. 실행 테스트..."
if ./bessel_roots > /dev/null 2>&1; then
    echo "   ✓ 실행 성공"
else
    echo "   ✗ 실행 실패"
    exit 1
fi

# 출력 파일 확인
echo "3. 출력 파일 확인..."
files=("results.csv" "method_stats.dat" "plot_results.gp")
for file in "${files[@]}"; do
    if [ -f "$file" ]; then
        echo "   ✓ $file 생성됨"
    else
        echo "   ✗ $file 누락"
    fi
done

# gnuplot 테스트 (선택적)
if command -v gnuplot > /dev/null 2>&1; then
    echo "4. 그래프 생성 테스트..."
    if gnuplot plot_results.gp > /dev/null 2>&1; then
        echo "   ✓ 그래프 생성 성공"
    else
        echo "   ⚠ 그래프 생성 실패 (gnuplot 문제?)"
    fi
else
    echo "4. gnuplot이 설치되지 않음 - 그래프 생성 건너뜀"
fi

echo "테스트 완료!"

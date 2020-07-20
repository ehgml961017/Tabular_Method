# Tabular_Method
논리회로 설계 과제 Quine-McCluskey Method

Quine-McCluskey Method
Sum-of-Product 형태의 논리식을 Quine-McCluskey 방법으로 모든 Prime Implicant를 도출하고,
이를 Essential Prime Implicant와 Non-Essential Prime Implicant로 구분하여 출력하는 코드를 작성하세요.

코드는 함수 형태로 작성하며, 함수의 인자(입력)와 출력(반환값)은 다음과 같이 정의합니다.

입력 인자

인자 형식: 정수 배열
[변수의 개수, minterm의 개수, minterm #1, minterm #2, ....]
예) [4, 7, 0, 1, 2, 3, 10, 11, 12] => 4개의 변수, 7개의 minterm
출력 값

출력 값 형식: 문자열 배열
모든 Prime Implicant를 각각 문자열로 출력합니다. 각 변수 자리에 '0', '1', 혹은 '-'를 출력합니다. '-'는 해당 자리에 값 2가 있는 것으로 계산해서 오름차순으로 정렬하여 출력합니다.
Prime Implicant 중 Essential Prime Implicant를 먼저 출력하고 그 후에 Non-Essential Prime Implicant를 출력합니다.
출력의 시작은 EPI로 시작하여 먼저 Essential Prime Implicant를 출력하고 바로 다음에 NEPI로 시작하여 나머지 Prime Implicant를 출력합니다. (문자열 EPI와 NEPI는 반드시 출력합니다.)
예) [EPI, 00-1, 1001, - -00, NEPI, 0000, 0011, 1-11, -000 ]
입출력 예

Input: [3, 6, 0, 1, 2, 5, 6, 7]
output: [EPI, NEPI, 00-, 0-0, 11-, 1-1, -01, -10]

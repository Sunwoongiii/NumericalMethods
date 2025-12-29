import numpy as np
from PIL import Image

def bilinear_interpolation(img, new_height, new_width):
    """
    이미지 배열 img를 (new_height, new_width)로 리샘플링 (양선형 보간)
    """
    orig_height, orig_width = img.shape[:2]

    # 컬러/흑백 지원
    if len(img.shape) == 3:
        channels = img.shape[2]
        resized = np.zeros((new_height, new_width, channels), dtype=np.uint8)
    else:
        channels = 1
        resized = np.zeros((new_height, new_width), dtype=np.uint8)

    # 스케일 비율
    x_ratio = (orig_width - 1) / (new_width - 1) if new_width > 1 else 0
    y_ratio = (orig_height - 1) / (new_height - 1) if new_height > 1 else 0

    for i in range(new_height):
        for j in range(new_width):
            x = j * x_ratio
            y = i * y_ratio
            x1 = int(np.floor(x))
            y1 = int(np.floor(y))
            x2 = min(x1 + 1, orig_width - 1)
            y2 = min(y1 + 1, orig_height - 1)
            dx = x - x1
            dy = y - y1

            if channels == 1:
                top = (1 - dx) * img[y1, x1] + dx * img[y1, x2]
                bottom = (1 - dx) * img[y2, x1] + dx * img[y2, x2]
                value = (1 - dy) * top + dy * bottom
                resized[i, j] = int(value)
            else:
                for c in range(channels):
                    top = (1 - dx) * img[y1, x1, c] + dx * img[y1, x2, c]
                    bottom = (1 - dx) * img[y2, x1, c] + dx * img[y2, x2, c]
                    value = (1 - dy) * top + dy * bottom
                    resized[i, j, c] = int(value)

    return resized

def main():
    # 1. 파일 읽기
    input_path = "image.jpg"  # 입력 파일명
    img = Image.open(input_path)
    img_array = np.array(img)
    print(f"원본 해상도: {img_array.shape[0]} x {img_array.shape[1]}")

    # 2. 목표 해상도 입력
    new_height = int(input("변환할 세로 크기(M'): "))
    new_width = int(input("변환할 가로 크기(N'): "))

    # 3. 리샘플링 실행
    print("리샘플링 중...")
    resized_img = bilinear_interpolation(img_array, new_height, new_width)

    # 4. 결과 저장
    result = Image.fromarray(resized_img)
    output_path = "resampled_image.jpg"
    result.save(output_path)
    print(f"완료! 저장 경로: {output_path}")

if __name__ == "__main__":
    main()

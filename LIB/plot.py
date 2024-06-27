import pandas as pd
import matplotlib.pyplot as plt


file_path = input("Nhập đường dẫn tới file CSV chứa dữ liệu : ")

try:
    with open(file_path, 'r') as f:
        first_line = f.readline().strip() # bỏ qua dòng đầu tiên
        first_line = f.readline().strip()
        if ';' in first_line: # có dâu ; là hợpn lệ vì sau dấu ; là biến dự đoán
            df = pd.read_csv(file_path, delimiter=';', skiprows=1)
            column_names = first_line.split(';')
        else:
            print("Không hợp lệ")
            exit()
except FileNotFoundError:
    print("Không hợp lệ")

coefficients_path = 'coefficients.csv'
try: # lấy hệ số phương trình
    with open(coefficients_path, 'r') as f:
        lines = f.readlines()
        if len(lines) < 2:
            print("File coefficients.csv không đủ dữ liệu")
            exit()
        intercept = float(lines[0].strip()) 
        slope = float(lines[1].strip())
except FileNotFoundError:
    print(f"Không tìm thấy file {coefficients_path}")
    exit()

df[column_names[0]] = pd.to_numeric(df[column_names[0]], errors='coerce') # số hoá 
df[column_names[1]] = pd.to_numeric(df[column_names[1]], errors='coerce')
df = df.dropna() # bỏ qua giá trị n/a

x = df[column_names[0]] # set lại thành các biến
y = df[column_names[1]]

plt.scatter(x, y, color='blue', label='Dữ liệu thực tế') # các điểm có dạng màu xanh
plt.plot(x, intercept + slope*x, color='red', label='Đường hồi quy tuyến tính')
# đường thẳng vẽ bằng phương trình tuyến tính
plt.xlabel(column_names[0]) # tên cột x
plt.ylabel(column_names[1]) # tên cột y
plt.title('Hồi quy tuyến tính của {} so với {}'.format(column_names[1], column_names[0]))

plt.legend()

plt.show()

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from sklearn.linear_model import LinearRegression

file_path = input("Nhập đường dẫn tới file CSV chứa dữ liệu: ")
coefficients_path = 'coefficients.csv'

try:
    with open(file_path, 'r') as file:
        header_line = file.readline().strip()
        column_names_line = file.readline().strip()

    column_names = column_names_line.split(',')
    df = pd.read_csv(file_path, skiprows=2, names=column_names)

    split_col = None
    for col in df.columns:
        if df[col].astype(str).str.contains(';').any():
            split_col = col
            break

    if split_col is None:
        raise ValueError("Không tìm thấy cột chứa dấu chấm phẩy để tách.")

    df_split = df[split_col].str.split(';', expand=True)
    original_col_name = column_names[df.columns.get_loc(split_col)]
    new_column_names = [f'{original_col_name}_{i}' for i in range(df_split.shape[1])]
    df_split.columns = new_column_names
    df = pd.concat([df, df_split], axis=1).drop(columns=[split_col])
    df = df.apply(pd.to_numeric, errors='coerce').dropna()

    material_col = column_names[0]
    concacc_col = new_column_names[0]
    octa_col = new_column_names[1] if len(new_column_names) > 1 else None

    x1 = df[material_col]
    x2 = df[concacc_col]
    y = df[octa_col]

    X = df[[material_col, concacc_col]]

    try:
        with open(coefficients_path, 'r') as f:
            lines = f.readlines()
            if len(lines) < 3:
                print("File coefficients.csv không đủ dữ liệu")
                exit()
            intercept = float(lines[0].strip())
            slope1 = float(lines[1].strip())
            slope2 = float(lines[2].strip())
    except FileNotFoundError:
        print(f"Không tìm thấy file {coefficients_path}")
        exit()
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    ax.scatter(x1, x2, y, color='blue', label='Dữ liệu thực tế')

    x1_range = np.linspace(df[material_col].min(), df[material_col].max(), 10)
    x2_range = np.linspace(df[concacc_col].min(), df[concacc_col].max(), 10)
    X1, X2 = np.meshgrid(x1_range, x2_range)
    Y_predicted = slope1 * X1 + slope2 * X2 + intercept

    ax.plot_surface(X1, X2, Y_predicted, alpha=0.5, color='red')

    ax.auto_scale_xyz([x1.min(), x1.max()], [x2.min(), x2.max()], [y.min(), y.max()])

    ax.set_xlabel(material_col)
    ax.set_ylabel(f'{original_col_name.split(";")[0]}')
    ax.set_zlabel(f'{original_col_name.split(";")[1]}')

    plt.title('Mô hình hồi quy tuyến tính 3D')

    plt.legend()
    plt.show()

except FileNotFoundError:
    print("File not found")
except Exception as e:
    print(f"Error: {e}")

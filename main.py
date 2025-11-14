import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Данные
df = pd.read_csv('input.csv', sep=', ', engine='python')
S_TRUE = 0.25 * np.pi + 1.25 * np.arcsin(0.8) - 1.0
print(df.head())

# График
plt.figure(figsize=(8, 5))
plt.plot(df['N'], df['S_est_wide'], label='Широкая рамка')
plt.plot(df['N'], df['S_est_small'], label='Узкая рамка')
plt.axhline(S_TRUE, color='black', label='Точное значение')
plt.xlabel('N')
plt.ylabel('S оценка')
plt.title('Оценка площади пересечения x N')
plt.xlim(left=0)
plt.grid()
plt.legend()
plt.tight_layout()
plt.show()

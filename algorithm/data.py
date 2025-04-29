import FinanceDataReader as fdr
import numpy as np
import matplotlib.pyplot as plt
import pickle
from tensorflow.keras import Sequential
from tensorflow.keras.layers import Dense, SimpleRNN, GRU, LSTM, Dropout
import os 
os.environ["CUDA_VISIBLE_DEVICES"] = "-1"

# 범위를 0 ~ 1 로 normalized
def MinMaxScaler(data):
    """최솟값과 최댓값을 이용하여 0 ~ 1 값으로 변환"""
    numerator = data - np.min(data, 0)
    denominator = np.max(data, 0) - np.min(data, 0)
    # 0으로 나누기 에러가 발생하지 않도록 매우 작은 값(1e-7)을 더해서 나눔
    return numerator / (denominator + 1e-7)

df = fdr.DataReader('005930', '2018-05-04', '2020-01-22')
dfx = df[['Open','High','Low','Volume', 'Close']]
dfx = MinMaxScaler(dfx)
dfy = dfx[['Close']]
dfx = dfx[['Open','High','Low','Volume']]

x = dfx.values.tolist() # open, high, log, volume, 데이터
y = dfy.values.tolist() # close 데이터

#ex) 1월 1일 ~ 1월 10일까지의 OHLV 데이터로 1월 11일 종가 (Close) 예측
#ex) 1월 2일 ~ 1월 11일까지의 OHLV 데이터로 1월 12일 종가 (Close) 예측
window_size = 10
data_x = []
data_y = []
for i in range(len(y) - window_size):
    _x = x[i : i + window_size] # 다음 날 종가(i+windows_size)는 포함되지 않음
    _y = y[i + window_size] # 다음 날 종가
    data_x.append(_x)
    data_y.append(_y)



train_size = int(len(data_y) * 0.7)
val_size = int(len(data_y) * 0.2)
train_x = np.array(data_x[0 : train_size])
train_y = np.array(data_y[0 : train_size])
val_x = np.array(data_x[train_size:train_size+val_size])
val_y = np.array(data_y[train_size:train_size+val_size])
test_size = len(data_y) - train_size - val_size
test_x = np.array(data_x[train_size+val_size: len(data_x)])
test_y = np.array(data_y[train_size+val_size: len(data_y)])
print('훈련 데이터의 크기 :', train_x.shape, train_y.shape)
print('검증 데이터의 크기 :', val_x.shape, val_y.shape)
print('테스트 데이터의 크기 :', test_x.shape, test_y.shape)



#RNN
model_rnn = Sequential()
model_rnn.add(SimpleRNN(units=20, activation='tanh', return_sequences=True, input_shape=(10, 4)))
model_rnn.add(Dropout(0.1))
model_rnn.add(SimpleRNN(units=20, activation='tanh'))
model_rnn.add(Dropout(0.1))
model_rnn.add(Dense(units=1))
model_rnn.summary()
model_rnn.compile(optimizer='adam', loss='mean_squared_error')
history_rnn = model_rnn.fit(train_x, train_y, validation_data = (val_x, val_y), epochs=70, batch_size=30)


#GRU
model_gru = Sequential()
model_gru.add(GRU(units=20, activation='tanh', return_sequences=True, input_shape=(10, 4)))
model_gru.add(Dropout(0.1))
model_gru.add(GRU(units=20, activation='tanh'))
model_gru.add(Dropout(0.1))
model_gru.add(Dense(units=1))
model_gru.summary()
model_gru.compile(optimizer='adam', loss='mean_squared_error') 
history_gru = model_gru.fit(train_x, train_y, validation_data = (val_x, val_y), epochs=70, batch_size=30)


#LSTM
model_lstm = Sequential()
model_lstm.add(LSTM(units=20, activation='tanh', return_sequences=True, input_shape=(10, 4)))
model_lstm.add(Dropout(0.1))
model_lstm.add(LSTM(units=20, activation='tanh'))
model_lstm.add(Dropout(0.1))
model_lstm.add(Dense(units=1))
model_lstm.summary()
model_lstm.compile(optimizer='adam', loss='mean_squared_error')
history_lstm = model_lstm.fit(train_x, train_y, validation_data = (val_x, val_y), epochs=70, batch_size=30)

pred_rnn = model_rnn.predict(test_x)
pred_gru = model_gru.predict(test_x)
pred_lstm = model_lstm.predict(test_x)
actual = test_y

# --- 그래프 출력 ---
plt.figure(figsize=(10, 6))
plt.plot(actual[:50], label='Actual', color='red')                    # 실제 종가
plt.plot(pred_rnn[:50], label='predicted (rnn)', color='blue')       # RNN 예측
plt.plot(pred_gru[:50], label='predicted (gru)', color='orange')     # GRU 예측
plt.plot(pred_lstm[:50], label='predicted (lstm)', color='green')    # LSTM 예측
plt.title('SEC stock price prediction')
plt.xlabel('time')
plt.ylabel('stock price')
plt.legend()
plt.grid(True)
plt.savefig('predicted_vs_actual.png')  # 이미지 저장
plt.show()

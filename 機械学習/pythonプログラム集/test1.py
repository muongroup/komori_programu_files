import keras
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Dropout
from keras.optimizers import RMSprop
import math
import numpy as np
import matplotlib.pyplot as plt
#from matplotlib import plt

#訓練データを128個に分割して学習
batch_size = 128
#0-9の10パターン
num_classes= 10
#訓練データを繰り返し学習させる回数
epochs = 25

#mnistからデータを持ってくる
(x_train,y_train), (x_test, y_test)=mnist.load_data()

#xがピクセルデータyが答え目的関数

#配列の形を変える
x_train = x_train.reshape(60000,784)


#x_split=np.vsplit(x_train,5)
x_test = x_test.reshape(10000,784)
#floatの形に型変換
x_train = x_train.astype('float32')
x_test = x_test.astype('float32')

#0-1の間で規格化
x_train /=255
x_test /=255
#print(x_split,'aa')
print(x_train.shape[0],'train samples')
print(x_test.shape[0],'train samples')

#yをkerasで扱いやすい形に変換
y_train = keras.utils.to_categorical(y_train, num_classes)
y_test = keras.utils.to_categorical(y_test, num_classes)

#モデルの作成
model = Sequential()
model.add(Dense(512,activation='relu',input_shape=(784,)))
model.add(Dropout(0.2))
model.add(Dense(512,activation='relu'))
model.add(Dropout(0.2))
#ソフトマックス関数(活性化関数)
model.add(Dense(num_classes,activation='softmax'))

#summaryは作ったモデルを画面に表示
model.summary()

model.compile(loss='categorical_crossentropy',optimizer=RMSprop(),metrics=['accuracy'])

#モデルにデータを入れ込む
result=model.fit(x_train, y_train, batch_size=batch_size, epochs=epochs,verbose=1,validation_data=(x_test,y_test))

#モデルを評価するところ
score = model.evaluate(x_test, y_test, verbose=0)
print('Test loss:',score[0])
print('Test accuracy:',score[1])


#画像を造る
loss=result.history['loss']
val_loss = result.history['val_loss']
acc = result.history['acc']
val_acc =result.history['val_acc']
plt.plot(range(epochs),loss,marker='.',label='loss')
plt.plot(range(epochs),val_loss,marker='.',label='val_loss')
plt.plot(range(epochs),acc,marker='.',label='acc')
plt.plot(range(epochs),val_acc,marker='.',label='val_acc')
plt.legend(loc='best')
plt.grid()
plt.xlabel('epoch')
plt.ylabel('acc')
plt.show()



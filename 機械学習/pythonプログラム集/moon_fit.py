import numpy as np
from keras.models import Sequential
from keras.layers import Dense,Activation
from keras.optimizers import SGD
from sklearn import datasets
from sklearn.model_selection import train_test_split
N=1000
X,y=datasets.make_moons(N,noise=0.3)
#print(np.shape(X))
#print(np.shape(y))
#print(X,y)
X_train,X_test,y_train,y_test=train_test_split(X,y,train_size=0.8)
#データを8:2に分ける

#出力層-隠れ層
model = Sequential() #層構造の定義
model.add(Dense(3,input_dim=2))#隠れ層のユニット3
model.add(Activation('sigmoid'))


#隠れ層より出力層
model.add(Dense(1))#出力層1
model.add(Activation('sigmoid'))


model.compile(loss='binary_crossentropy',optimizer=SGD(lr=0.5),metrics=['accuracy'])
#accuracyと書くだけで制度の値を出してくれる

model.fit(X_train,y_train,epochs=500,batch_size=20)#学習させているところ

loss_and_metrics = model.evaluate(X_test,y_test)

print(loss_and_metrics)

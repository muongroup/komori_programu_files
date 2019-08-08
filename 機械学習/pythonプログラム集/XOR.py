import numpy as np
from keras.models import Sequential
from keras.layers import Dense, Activation
from keras.optimizers import SGD

np.random.seed(0)

#XORゲート
X=np.array([[0,0],[0,1],[1,0],[1,1]])
#print(np.shape(X))
Y=np.array([[0],[1],[1],[0]])
#print(np.shape(Y))


model = Sequential()

#入力層-隠れ層
model.add(Dense(input_dim=2,units=2))
model.add(Activation('sigmoid'))

#隠れ層-出力層
model.add(Dense(units=1))
model.add(Activation('sigmoid'))

model.compile(loss='binary_crossentropy',optimizer=SGD(lr=0.1))

model.fit(X,Y,epochs=4000,batch_size=4)#データを入れ込むところ

classes = model.predict_classes(X,batch_size=4)
#print(classes)
prob=model.predict_proba(X,batch_size=4)
print('clasified:')
print(Y==classes)
print()
print('output probability:')
print(prob)

#print()



import random

random.seed(0)

addrList = []

maxPage = 10
numAdress = 30
probPass = 0.6

lastCnt = 3
for _ in range(numAdress):
	 now = int(maxPage * random.random())

	 probChoose = random.random()
	 addrList.append(now)

	 if probChoose < probPass: # повторяется один из lastCnt последних элементов
	 		now_ind = random.randint(0, min(lastCnt, len(addrList) - 1))
	 		addrList[len(addrList) - 1] = addrList[len(addrList) - 1 - now_ind]

print(*addrList, sep=",")	



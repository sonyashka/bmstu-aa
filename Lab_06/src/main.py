import copy
import random
from random import randint
import \
    numpy as np
import itertools
from time import process_time
from numpy.random import choice as np_choice


def calc_dist(array, distances):
    cost = 0
    for i in range(len(array) - 1):
        cost += distances[array[i]][array[i + 1]]
    return cost
def permut(matr):
    arr = list(range(len(matr)))
    permut_arr = list(itertools.permutations(arr))
    for i in range(len(permut_arr)):
        permut_arr[i] = list(permut_arr[i])
        permut_arr[i].append(permut_arr[i][0])
    costs = [calc_dist(x, matr) for x in permut_arr]
    return min(costs), permut_arr[costs.index(min(costs))]

# функция для считывания входящих данных
def read_input():
    data = []
    line = True
    while line:
        line = input().split()
        if line:
            data.append(line)
    matrix = np.array(data, float)
    return matrix

def random_matrix2(n, a, b, per):
    mat = []
    k = int (n * per)
    for i in range(n):
        mat.append([])
        for j in range(n):
            mat[i].append(0)
    for i in range(n):
        for j in range(i):
            r = randint(a, b)
            mat[i][j] = r
            mat[j][i] = r
    for _ in range(k):
        number = randint(0, n*n)
        i = int(number/n)
        j = number-int(number/n)*n
        if i and j:
            mat[i][j] = 0
            mat[j][i] = 0
    data = np.array(mat, float)
    for i in range(n):
        for j in range(n):
            if data[i][j] == 0:
                data[i][j] = 10000000
    return data
def random_matrix(n, a, b):
    mat = []
    for i in range(n):
        mat.append([])
        for j in range(n):
            mat[i].append(0)
    for i in range(n):
        for j in range(i):
            r = randint(a, b)
            mat[i][j] = r
            mat[j][i] = r
    data = np.array(mat, float)
    for i in range(n):
        for j in range(n):
            if data[i][j] == 0:
                data[i][j] = 10000000
    return data
class ant(object):
    def __init__(self):
        self.way = []
        self.start = 0
        self.dist = 0
        self.notvisited = []

class AntColony(object):
    def __init__(self, distances, decay, tmax, alpha=0.5, beta=0.5, e=0):
        self.distances  = distances #матрица растояний
        for i in range(len(distances)):
            for j in range(len(distances)):
                if self.distances[i][j] == 0:
                    self.distances[i][j] = 10000000
        self.pheromone = np.ones(self.distances.shape) / len(distances) # данные о феромонах
        self.all_inds = list(range(len(distances))) # список городов
        self.decay = decay # испарения феромона
        self.alpha = alpha
        self.beta = beta
        self.tmax = tmax
        self.count = len(distances)
        self.ants = []
        self.n_elits = e
        self.q = sum([sum(x) for x in distances])*2


    def run(self):
        self.ants = self.allocation_ants()
        best_way = copy.deepcopy(self.all_inds)
        best_way.append(self.all_inds[0])
        least_dist = self.calc_dist(best_way)
        for t in range(int(self.tmax)):
            self.ants = self.allocation_ants()
            for a in range(self.count - 1):
                self.choose_way()
            for i in range(self.count):
                self.ants[i].way.append(self.ants[i].way[0])
                self.ants[i].dist = self.calc_dist(self.ants[i].way)
                if self.ants[i].dist < least_dist:
                    least_dist = self.ants[i].dist
                    best_way = copy.deepcopy(self.ants[i].way)
            dt = self.correct_pheromones()
            self.elit(best_way, dt)
        return best_way
    def correct_pheromones(self):
        delta_tao = 0
        for i in range(self.count):
            delta_tao += self.q / self.ants[i].dist
        for i in range(self.count):
            for j in range(len(self.ants[i].way)-1):
                start = self.ants[i].way[j]
                finish = self.ants[i].way[j+1]
                self.pheromone[start][finish] = self.pheromone[start][finish] * (1 - self.decay) + delta_tao
                self.pheromone[finish][start] = self.pheromone[finish][start] * (1 - self.decay) + delta_tao
                if self.pheromone[start][finish] < 1 / len(self.distances):
                    self.pheromone[start][finish] = 1 / len(self.distances)
                if self.pheromone[finish][start] < 1 / len(self.distances):
                    self.pheromone[finish][start] = 1 / len(self.distances)
        return delta_tao
    def calc_dist(self, array):
        cost = 0
        for i in range(len(array)-1):
            cost += self.distances[array[i]][array[i+1]]
        return cost
    def allocation_ants(self):
        starts = []
        ants = []
        for i in range(self.count):
            cur_ant = ant()
            a = randint(0, self.count - 1)
            while a in starts:
                a = randint(0, self.count - 1)
            starts.append(a)
            cur_ant.start = a
            cur_ant.way.append(a)
            cur_ant.notvisited = copy.deepcopy(self.all_inds)
            cur_ant.notvisited.remove(a)
            ants.append(cur_ant)
        return ants

    def choose_city(self, index):
        denominator = 0
        last_city = self.ants[index].way[-1]
        for i in range(len(self.ants[index].notvisited)):
            cost = 1 / self.distances[last_city][self.ants[index].notvisited[i]]
            tao = self.pheromone[last_city][self.ants[index].notvisited[i]]
            denominator += cost ** self.beta + tao ** self.alpha
        pvision = []
        for i in range(len(self.ants[index].notvisited)):
            cost = 1 / self.distances[last_city][self.ants[index].notvisited[i]]
            tao = self.pheromone[last_city][self.ants[index].notvisited[i]]
            p = cost ** self.beta + tao ** self.alpha
            if i == 0:
                pvision.append(p/denominator)
            else:
                pvision.append(pvision[i - 1] + p/denominator)
        probability = random.random()
        i = 0
        if len(pvision) == 1:
            i = 0
        else:
            while pvision[i] < probability:
                i += 1
        self.ants[index].way.append(self.ants[index].notvisited[i])
        self.ants[index].notvisited.pop(i)
    def choose_way(self):
        for i in range(self.count):
            self.choose_city(i)
    def elit(self, bestway, delta_tao):
        for i in range(int(self.n_elits)):
            for j in range(len(bestway)-1):
                self.pheromone[bestway[j]][bestway[j+1]] += delta_tao
                self.pheromone[bestway[j + 1]][bestway[j]] += delta_tao


def analyse1():
    lens = [11]
    print("{0:5}{1:10}{2:10}".format("len", "time1", "time2"))
    for l in lens:
        t1 = 0
        t2 = 0
        for j in range (5):
            distance = random_matrix(l, 0, 50)
            worker = AntColony(distance, 0.2, 8000, 0.5, 0.5, 3) #len(distance), 0.2, 8000, 0.5, 0.5, 3)
            start = process_time()
            res = worker.run()
            end = process_time()
            t1 += end - start
            start = process_time()
            res = permut(distance)
            end = process_time()
            t2 += end - start
        print("{0:<5}{1:<10.2}{2:<10.2}".format(l, t1/5, t2/5))
def analyse2():
    alpha = list(np.arange(0, 1.1, 0.1))
    ps = [0, 0.3, 0.5, 0.7, 1]
    print("{0:<10}{1:<10}{2:<10}{3:<10}{4:<10}".format("alpha", "betta", "p", "tresult","diff"))
    mat = random_matrix(3, 0, 1000000)
    cor_res = permut(mat)[0]
    for a in alpha:
        for p in ps:
            tmin = 6000
            worker = AntColony(mat, p, tmin, a, 1-a, 3)
            res = worker.calc_dist(worker.run())
            while cor_res != res and tmin <= 10000:
                tmin += 1000
                worker = AntColony(mat, p, tmin, a, 1-a, 3)
                res = worker.calc_dist(worker.run())
            while cor_res == res:
                tmin -= 500
                worker = AntColony(mat, p, tmin, a, 1-a, 3)
                res = worker.calc_dist(worker.run())
            print("{0:<10}{1:<10}{2:<10}{3:<10}{4:<10}".format(a, 1-a, p, tmin + 500, (abs(res - cor_res)) if tmin >= 10000 else 0))

# alpha = list(np.arange(0, 1.1, 0.1))
# ps = [0, 0.3, 0.5, 0.7, 1]
# print("{0:<10}{1:<10}{2:<10}{3:<10}{4:<10}".format("alpha", "betta", "p", "tresult","diff"))
# mat = random_matrix2(10, 0, 1000,0.5)
# cor_res = permut(mat)[0]
# for a in alpha:
#     for p in ps:
#         tmin = 6000
#         worker = AntColony(mat, p, tmin, a, 1-a, 3)
#         res = worker.calc_dist(worker.run())
#         while cor_res != res and tmin <= 10000:
#             tmin += 1000
#             worker = AntColony(mat, p, tmin, a, 1-a, 3)
#             res = worker.calc_dist(worker.run())
#         while cor_res == res:
#             tmin -= 500
#             worker = AntColony(mat, p, tmin, a, 1-a, 3)
#             res = worker.calc_dist(worker.run())
#         print("{0:<10}{1:<10}{2:<10}{3:<10}{4:<10}".format(a, 1-a, p, tmin + 500, (abs(res - cor_res)) if tmin >= 10000 else 0))

#
mode = 1
while mode in [1, 2, 3]:
    mode = int(input('Введите режимы работы:\n1 - ручное тестирование,\n2 - исследование времени,\n3 - параметризация муравьиного алгоритма\n'))
    if mode == 1:
        print("Введите матрицу расстояний.")
        distance=read_input()
        a, p, t, e = list(map(float, input("Введите параметры для муравьиного алгоритма alpha, p, t_iter, elits:\n").split()))
        b = 1 - a
        worker = AntColony(distance,p, t, a, b, e) #len(distance), p, t, a, b, e)
        start = process_time()
        res = worker.run()
        end = process_time()
        print("Result 1:")
        print("Best way:", res)
        print("Best length:", worker.calc_dist(res))
        print("TIME1")
        print((end - start)*1e6)
#
        start = process_time()
        res = permut(distance)[1]
        end = process_time()
        print("Result 2:")
        print("Best way:", res)
        print("Best length:", calc_dist(res, distance))
        print("TIME2")
        print((end - start)*1e6)
    elif mode == 2:
        analyse1()
    elif mode == 3:
        analyse2()
    else:
        exit(1)
# distance = random_matrix(10, 0, 50)
# print(distance)

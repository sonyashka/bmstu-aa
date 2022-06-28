package main

import (
	"errors"
	"fmt"
	"io"
	"os"

	"./find"
)

func main() {
	d := ReadData()
	var action int
	var key int
	iter := 0
	for action != 4 {
		action = ChooseAction()
		for action == -1 {
			action = ChooseAction()
		}
		if action == 1 {
			PrintTableDict(d)
		}
		if action == 2 {
			key = GetKey()
			for key == -1 {
				key = GetKey()
			}

			fmt.Println()
			fmt.Println("Поиск методом частотного анализа: ")
			fmt.Printf("dictionary[%v] = %v\n", key, find.FreqFind(d, key, &iter))
			fmt.Printf("Число итераций: %v\n", find.CountCmpFreqFind(d, key))

			fmt.Println()
			fmt.Println("Поиск методом полного перебора: ")
			fmt.Printf("dictionary[%v] = %v\n", key, find.BruteForce(d, key, &iter))
			fmt.Printf("Число итераций: %v\n", find.CountCmpBruteForce(d, key))

			fmt.Println()
			fmt.Println("Поиск методом бинарного поиска: ")
			fmt.Printf("dictionary[%v] = %v\n", key, find.BinarySearch(d, key, &iter))
			fmt.Printf("Число итераций: %v\n", find.CountCmpBinarySearch(d, key))
		}
		if action == 3 {
			find.LogBruteForce(d)
			find.LogBinarySearch(d)
			find.LogFreqFind(d)
		}
	}
}

func PrintTableDict(dict find.Dict_t) {
	fmt.Println("Dictionary:")
	for i := 0; i < len(dict); i += 4 {
		for j := 0; j < 4 && (j+i) < len(dict); j++ {
			fmt.Printf("|%5v -> %20v  ", i+j+1, dict[i+j])
		}
		fmt.Println("|")
	}
}

func PrintTextDict() {
	fmt.Println()
	fmt.Println("Dictionary:")
	f, _ := os.Open("data/fairytale.txt")

	var err error
	var temp string
	_, err = fmt.Fscanf(f, "%s", &temp)
	for !errors.Is(err, io.EOF) {
		fmt.Printf("%s ", temp)
		_, err = fmt.Fscanf(f, "%s", &temp)
	}
	f.Close()
	fmt.Println()
}

func ReadData() find.Dict_t {
	dict := make(find.Dict_t)
	f, _ := os.Open("data/data_novel.txt")

	var err error
	var temp string
	_, err = fmt.Fscanf(f, "%s", &temp)
	i := 0
	for err == nil {
		dict[i] = temp
		i += 1
		_, err = fmt.Fscanf(f, "%s", &temp)
	}
	f.Close()
	return dict
}

func ChooseAction() int {
	var (
		action int
		err    error
	)

	fmt.Println()
	fmt.Println("Выберите действие:")
	fmt.Println("1) Вывести данные из словаря в табличном формате")
	fmt.Println("2) Найти значение в словаре по ключу")
	fmt.Println("3) Логировать характеристики алгоритмов в файлы")
	fmt.Println("4) Завершить программу")
	fmt.Println()
	fmt.Print("Ваш ответ: ")
	fmt.Scan(&action)

	if err != nil || action < 1 || action > 4 {
		fmt.Println("Ошибка ввода. Должно быть введено целое число, являющееся одним из пунктов меню.")
		return -1
	}

	return action
}

func GetKey() int {
	var key int
	var err error
	fmt.Println()
	fmt.Print("Введите значение ключа: ")
	fmt.Scan(&key)
	if err != nil || key < 0 {
		fmt.Println("Ошибка ввода. Должно быть введено целое неотрицательное число.")
		return -1
	}
	return key
}

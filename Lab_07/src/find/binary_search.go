package find

import (
	"fmt"
	"os"
)

func BinarySearch(dict Dict_t, key int, iter *int) string {
	var (
		left  int
		right int
		mid   int
	)

	left = 0
	right = len(dict) - 1
	*iter = 0

	if right != 0 {
		for left <= right {
			*iter += 1
			mid = left + (right-left)/2
			if mid == key-1 {
				return dict[mid]
			}
			if mid < key-1 {
				left = mid + 1
			} else {
				right = mid - 1
			}
		}
	}
	return "ERROR:NOT_FOUND"
}

func LogBinarySearch(dict Dict_t) {
	f, _ := os.Create("data/log_bs.txt")
	var cmps int
	for i := 0; i < len(dict); i += 6 {
		for j := 0; j < 6; j++ {
			cmps = CountCmpBinarySearch(dict, i+j+1)
			fmt.Fprintf(f, "%v %v\n", i+j+1, cmps)
		}
	}
}

func CountCmpBinarySearch(dict Dict_t, key int) int {
	var (
		left  int
		right int
		mid   int
		cmps  int
	)

	left = 0
	right = len(dict) - 1
	cmps = 0

	if right != 0 {
		for left <= right {
			cmps += 1
			mid = left + (right-left)/2
			if mid == key-1 {
				return cmps
			}
			if mid < key-1 {
				left = mid + 1
			} else {
				right = mid - 1
			}
		}
	}
	return cmps
}

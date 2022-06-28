package find

import (
	"fmt"
	"os"
	"strings"
)

var alphabet = string("abcdefghijklmnopqrstuvwxyz")
var mask = make([]int, len(alphabet))

func find_pos(a string) int {
	pos := -1
	for i := 0; i < len(alphabet) && pos == -1; i++ {
		if string(alphabet[i]) == a {
			pos = i
		}
	}
	return pos
}

func swap_segs(s []Segment_t, i int, j int) {
	temp := s[i]
	s[i] = s[j]
	s[j] = temp
}

func swap_in_int_arr(a []int, i int, j int) {
	temp := a[i]
	a[i] = a[j]
	a[j] = temp
}

func sort_keys(keys []int) {
	for i := 0; i < len(keys)-1; i++ {
		for j := 0; j < len(keys)-i-1; j++ {
			if keys[j] > keys[j+1] {
				swap_in_int_arr(keys, j, j+1)
			}
		}
	}
}

func init_mask() {
	for i := 0; i < len(alphabet); i++ {
		mask[i] = i
	}
}

func create_segments(size int) []Segment_t {
	segments := make([]Segment_t, size)
	for i := 0; i < size; i++ {
		segments[i] = make(Segment_t)
	}
	return segments
}

func divide_by_first_letter(segments []Segment_t, dict Dict_t) {
	for i := 0; i < len(dict); i++ {
		index := find_pos(strings.ToLower(string(dict[i][0])))
		segments[index][i] = dict[i]
	}
}

func sort_by_size(segments []Segment_t) {
	for i := 0; i < len(segments)-1; i++ {
		for j := 0; j < len(segments)-i-1; j++ {
			if len(segments[j]) < len(segments[j+1]) {
				swap_segs(segments, j, j+1)
				swap_in_int_arr(mask, j, j+1)
			}
		}
	}
}

func binary_search(segments []Segment_t, key int, iter *int) string {
	var (
		left  int
		right int
		mid   int
	)

	for i := 0; i < len(segments); i++ {
		var keys = make([]int, 0)
		for key := range segments[i] {
			keys = append(keys, key)
		}
		sort_keys(keys)

		left = 0
		right = len(segments[i]) - 1

		if right != 0 {
			for left <= right {
				*iter += 1
				mid = left + (right-left)/2
				if keys[mid] == key {
					return segments[i][keys[mid]]
				}
				if keys[mid] < key {
					left = mid + 1
				} else {
					right = mid - 1
				}
			}
		}
	}
	return "ERROR:NOT_FOUND"
}

func FreqFind(dict Dict_t, key int, iter *int) string {

	init_mask()
	*iter = 0

	segments := create_segments(len(alphabet))

	divide_by_first_letter(segments, dict)

	sort_by_size(segments)

	return binary_search(segments, key-1, iter)
}

func log_binary_search(segments []Segment_t, key int) int {
	var (
		left  int
		right int
		mid   int
		cmps  int
	)

	for i := 0; i < len(segments); i++ {
		var keys = make([]int, 0)
		for key := range segments[i] {
			keys = append(keys, key)
		}
		sort_keys(keys)

		left = 0
		right = len(segments[i]) - 1
		cmps = 0

		if right != 0 {
			for left <= right {
				cmps += 1
				mid = left + (right-left)/2
				if keys[mid] == key {
					return cmps
				}
				if keys[mid] < key {
					left = mid + 1
				} else {
					right = mid - 1
				}
			}
		}
	}
	return cmps
}

func CountCmpFreqFind(dict Dict_t, key int) int {
	init_mask()
	segments := create_segments(len(alphabet))
	divide_by_first_letter(segments, dict)
	sort_by_size(segments)
	return log_binary_search(segments, key-1)
}

func LogFreqFind(dict Dict_t) {
	f, _ := os.Create("data/log_ff.txt")
	var cmps int
	for i := 0; i < len(dict); i += 6 {
		for j := 0; j < 6; j++ {
			cmps = CountCmpFreqFind(dict, i+j+1)
			fmt.Fprintf(f, "%v %v\n", i+j+1, cmps)
		}
	}
}

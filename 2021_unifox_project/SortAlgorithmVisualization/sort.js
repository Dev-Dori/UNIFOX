function shuffle(a) {    //배열을 섞어줌
    var j, x, i;  
    for (i = a.length; i; i -= 1) { 
        j = Math.floor(Math.random() * i); 
        x = a[i - 1]; 
        a[i - 1] = a[j]; 
        a[j] = x; 
    }  
} 



function arr_list(){
    arr = [];
    for(var i=1;i<=200;i++){
        arr[i-1] = i;
    }
    shuffle(arr);
}

function print_first(sort_arr){
    var main = document.getElementById("sort_board");
    var list;
    for(var i=0; i<200;i++){
        list = document.createElement('div');
        list.style.height = String(sort_arr[i]/2)+"%";
        list.id = String(i);
        list.className = "arr_list";
        list.style.width = "1%";
        list.style.backgroundColor="orange";
        main.appendChild(list);
    }
    return;
}

function button_over(tmp){
    tmp.style.backgroundColor = "orange";
}

function button_down(tmp){
    tmp.style.backgroundColor = "white";
}



var arr;
var array;
var bubble_sortid = null;
var quick_sortid = null;
var select_sortid = null;
var i = 0;
var j = 0;
//######################  ---  버블 정렬 --- ##########################//
function b_sort(){
    i=0;j=0;
    bubble_sortid = setInterval(function(){
        var temp;
        if(i<array.length){
            if (array[j] > array[j + 1]) { // 두 수를 비교하여 앞 수가 뒷 수보다 크면
                temp = array[j]; // 두 수를 서로 바꿔준다
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
            
            for(var a=0;a<array.length;a++){
                document.getElementById(String(a)).style.height = String(array[a]/2)+"%"; //array[i]
            }
            j++;
            
        }else if(j > array.length - 1 - i){
            i++;
            j=0;
        }
        
        if(i>array.length){
            i=0;
            j=0;
            clearInterval(bubble_sortid);
        }
        i++;
    },20);
}

function bubble_sort(){
    for(var a=0;a<200;a++){
        b_sort();
    }
}

//######################  ---  선택 정렬 --- ##########################//
function s_sort(){
    i=0;j=0;
    select_sortid = setInterval(function(){
        var min, index,temp;
        min = 1000;
        for(j=i;j<=array.length;j++){
            if(min > array[j]){
                index = j;
                min = array[j];
            }
        }

        temp = array[i];
        array[i] = min;
        array[index] = temp;

        for(var a=0;a<array.length;a++){
            document.getElementById(String(a)).style.height = String(array[a]/2)+"%"; //array[i]
        }

        i++;
        if(i > array.length){
            clearInterval(select_sortid);
        }
    },50);
}

function select_sort(){
    s_sort();
}


//######################  ---  퀵 정렬 --- ##########################//
const mod_arr = [];

function q_sort(){
    i=0;j=0;
    quick_sortid = setInterval(function(){
        for(var a=0;a<array.length;a++){
            document.getElementById(String(a)).style.height = String(mod_arr[0]/2)+"%"; //array[i]
            mod_arr.shift();
        }
        if(i==mod_arr.length/100){
            clearInterval(quick_sortid);
        }
        i++;
    },50);
}

function Swap(arr, idx1, idx2) { 
	var temp;
	temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp; 
}

 

function Partition(arr, left, right) {
	var pivot = arr[left];
	low = left + 1;
	high = right;

	while (low <= high) {	// 교차되지 않을 때까지 반복
		// 피벗보다 큰 값을 찾는 과정
		while (low <= right  && pivot >= arr[low]) low++;
		// 피벗보다 작은 값을 찾는 과정
		while (high >= (left+1) && pivot <= arr[high])  high--;
		// 교차되지 않는 상태라면 Swap 실행
		if (low <= high) { 	
			Swap(arr, low, high);
		}
	}
	Swap(arr, left, high);		// 피벗과 high 가 가리키는 대상 교환
	return high;					// 옮겨진 피벗의 위치정보 교환
}

 

function QuickSort(arr, left, right) {
	if (left < right) {
		pivot = Partition(arr, left, right); 
        for(var a=0;a<arr.length;a++){
            mod_arr[i++] = arr[a];
        }
		QuickSort(arr, left, pivot - 1);
		QuickSort(arr, pivot + 1, right);
	}
}


function quick_sort(){
    i=0,j=0;
    QuickSort(array,0,array.length-1);
    q_sort();
}


window.onload=function(){
    arr_list();
    print_first(arr); 
    array = arr;   
    clearInterval(bubble_sortid);
}
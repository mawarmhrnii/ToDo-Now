#include <stdio.h> // Library untuk fungsi input-output standar
#include <stdlib.h> // Library untuk fungsi umum, termasuk fungsi system()
#include <string.h> // Library untuk fungsi string

#define MAX_TASKS 100 // Mendefinisikan konstanta MAX_TASKS dengan nilai 100

typedef struct { // Deklarasi tipe data struktur Task
    char name[50]; // Atribut name bertipe array of char dengan ukuran 50
    int priority; // Atribut priority bertipe integer
    int isDone; // Atribut isdone bertipe integer
} Task;

typedef struct { // Deklarasi tipe data struktur Task taks
    Task tasks[MAX_TASKS]; // Array of Task untuk menyimpan tugas-tugas
    int size; // Ukuran heap (jumlah tugas saat ini)
} Heap;

void initHeap(Heap* heap) { //menginisialisasi heap dengan mengatur ukurannya menjadi 0, sehingga menghasilkan heap kosong.
    heap->size = 0; // Menginisialisasi ukuran heap menjadi 0 (heap kosong)
}

void swap(Task* a, Task* b) {// Fungsi untuk menukar dua elemen tipe data Task
    Task temp = *a; // Simpan nilai Task a ke variabel temp
    *a = *b; // Isi nilai Task a dengan nilai Task b
    *b = temp; // Isi nilai Task b dengan nilai temp (nilai awal Task a)
}

void heapifyUp(Heap* heap, int index) {  // Fungsi untuk memperbaiki ke atas heap setelah penambahan elemen
    if (index == 0) { // Basis kasus: jika index adalah root, tidak ada yang perlu diperbaiki
        return; // Jika sudah mencapai root node (indeks 0), berhenti
    }

    int parentIndex = (index - 1) / 2; // Hitung indeks parent (ortu) dari indeks saat ini
    if (heap->tasks[index].priority < heap->tasks[parentIndex].priority) { //memeriksa apakah prioritas elemen pada indeks index lebih kecil dari prioritas parent pada indeks parentIndex. Jika kondisi ini terpenuhi, dilakukan pertukaran elemen tersebut dengan parent menggunakan fungsi swap(). Setelah itu, dilakukan pemanggilan rekursif heapifyUp() untuk melanjutkan pemrosesan ke atas heap.
        swap(&heap->tasks[index], &heap->tasks[parentIndex]); // Jika prioritas tugas saat ini lebih kecil dari prioritas tugas orang tua, tukar posisinya
        heapifyUp(heap, parentIndex); // Rekursif: Panggil heapifyUp untuk indeks parent
    }
}

void heapifyDown(Heap* heap, int index) {// Fungsi untuk memperbaiki ke bawah heap setelah penambahan elemen
    int leftChildIndex = 2 * index + 1; // Hitung indeks child kiri
    int rightChildIndex = 2 * index + 2; // Hitung indeks child kanan
    int smallest = index; // Variabel untuk menyimpan indeks dengan prioritas terkecil

    if (leftChildIndex < heap->size && heap->tasks[leftChildIndex].priority < heap->tasks[smallest].priority) { //memeriksa apakah prioritas elemen pada indeks index lebih kecil dari prioritas parent pada indeks parentIndex. Jika kondisi ini terpenuhi, dilakukan pertukaran elemen tersebut dengan parent menggunakan fungsi swap(). Setelah itu, dilakukan pemanggilan rekursif heapifyUp() untuk melanjutkan pemrosesan ke atas heap.
        smallest = leftChildIndex; // Jika prioritas tugas child kiri lebih kecil dari prioritas tugas terkecil saat ini, simpan indeksnya
    }

    if (rightChildIndex < heap->size && heap->tasks[rightChildIndex].priority < heap->tasks[smallest].priority) { //  memerika elemen pada index
        smallest = rightChildIndex; // Jika prioritas tugas child kanan lebih kecil dari prioritas tugas terkecil saat ini, simpan indeksnya
    }

    if (smallest != index) { // / Jika indeks terkecil (smallest) tidak sama dengan indeks saat ini (index),
                            // dilakukan pertukaran elemen tersebut dengan elemen pada indeks.
        swap(&heap->tasks[index], &heap->tasks[smallest]); // Jika ada tugas dengan prioritas lebih kecil, tukar posisinya
        heapifyDown(heap, smallest); // Rekursif: Panggil heapifyDown untuk indeks smallest (indeks tugas yang ditukar)
    }
}

void addTask(Heap* heap) { // Memeriksa apakah ukuran heap (size) sudah mencapai batas maksimal (MAX_TASKS)
    if (heap->size == MAX_TASKS) {  // Jika heap penuh (sudah mencapai batas MAX_TASKS), tampilkan pesan kesalahan
        printf("Heap is full. Cannot add more tasks.\n"); // Jika heap penuh (sudah mencapai batas MAX_TASKS), tampilkan pesan kesalahan
        return; // Menghentikan eksekusi fungsi addTask dan kembali ke pemanggil
    }

    Task newTask; // Mendeklarasikan variabel newTask bertipe Task untuk menyimpan informasi tugas baru
    printf("Enter task name: "); getchar(); // Menampilkan pesan untuk meminta pengguna memasukkan nama tugas
    scanf("%[^\n]", newTask.name); getchar();  // Membaca nama tugas dari pengguna dan menyimpannya di atribut name dari newTask

    printf("Enter priority (1: Most Important, 2: Important, 3: Least Important): "); // Menampilkan pesan untuk meminta pengguna memasukkan prioritas tugas
    scanf("%d", &newTask.priority); // Membaca prioritas tugas dari pengguna

    if (newTask.priority < 1 || newTask.priority > 3) { // Memeriksa apakah prioritas tugas valid (di antara 1 hingga 3)
        printf("Invalid priority value. Task not added.\n"); // Jika prioritas tugas tidak valid, tampilkan pesan kesalahan
        return; // Menghentikan eksekusi fungsi addTask dan kembali ke pemanggil
    }

    newTask.isDone = 0; // Mengatur nilai isDone dari newTask menjadi 0, menunjukkan bahwa tugas tersebut belum selesai.

    heap->tasks[heap->size] = newTask; // Menyimpan newTask ke dalam array tasks pada posisi heap->size, menambahkan tugas baru ke dalam heap.
    heapifyUp(heap, heap->size); // Memastikan tugas baru ditempatkan pada posisi yang tepat dalam heap berdasarkan prioritasnya dengan memanggil fungsi heapifyUp.
    heap->size++; // Menambahkan ukuran heap (heap->size) setelah tugas baru ditambahkan.


    printf("Task added successfully.\n"); // menampilkan pesan 
}

void removeTask(Heap* heap) {
    if (heap->size == 0) { // Memeriksa apakah heap kosong
        printf("Heap is empty. No tasks to remove.\n"); // Menampilkan pesan bahwa heap kosong dan tidak ada tugas yang dapat dihapus
        return;
    }

    printf("List of all tasks:\n");// Menampilkan pesan
    printf("+--------------+----------+-------+\n");// Menampilkan pesan
    printf("|     Name     | Priority | Done? |\n");// Menampilkan pesan
    printf("+--------------+----------+-------+\n");// Menampilkan pesan
    for (int i = 0; i < heap->size; i++) {
        if (!heap->tasks[i].isDone) {
            printf("| %-12s |    %-3d   |   %s   |\n", heap->tasks[i].name, heap->tasks[i].priority, heap->tasks[i].isDone ? "Yes" : "No");
        }
    }
    printf("+--------------+----------+-------+\n");

    char taskName[50];
    printf("Enter task name to remove: "); getchar(); // menampilkan pesan 
    scanf("%[^\n]", taskName); getchar();

    int found = 0;
    int i;
    for (i = 0; i < heap->size; i++) { // Melakukan iterasi untuk mencari tugas dengan nama yang sesuai
        if (strcmp(heap->tasks[i].name, taskName) == 0) { // Membandingkan nama tugas dengan nama yang diinputkan
            found = 1; // Menandakan bahwa tugas ditemukan
            break;
        }
    }

    if (found) { // Jika tugas ditemukan
        heap->tasks[i] = heap->tasks[heap->size - 1]; // Menggantikan tugas yang ingin dihapus dengan tugas terakhir dalam heap
        heap->size--; // Mengurangi ukuran heap
        heapifyDown(heap, i); // Menjaga properti heap dengan memanggil fungsi heapifyDown
        printf("Task removed successfully.\n");// Menampilkan pesan

        printf("\nList of all tasks after removal:\n");// Menampilkan pesan
        printf("+--------------+----------+-------+\n");// Menampilkan pesan
        printf("|     Name     | Priority | Done? |\n");// Menampilkan pesan
        printf("+--------------+----------+-------+\n"); // Menampilkan pesan
        for (int i = 0; i < heap->size; i++) {
            if (!heap->tasks[i].isDone) {
                printf("| %-12s |    %-3d   |   %s   |\n", heap->tasks[i].name, heap->tasks[i].priority, heap->tasks[i].isDone ? "Yes" : "No");
            }
        }
        printf("+--------------+----------+-------+\n");// Menampilkan pesan
    } else {
        printf("Task not found.\n");// Menampilkan pesan
    }
}


void retrieveHighestPriorityTask(Heap* heap) {
    if (heap->size == 0) { // Memeriksa apakah heap kosong
        printf("No tasks to retrieve.\n"); // Menampilkan pesan bahwa tidak ada tugas yang dapat diambil
        return;
    }

    printf("Highest Priority Task:\n"); //tampilkan pesan 
    printf("+--------------+----------+-------+\n"); //tampilkan pesan 
    printf("|     Name     | Priority | Done? |\n");//tampilkan pesan 
    printf("+--------------+----------+-------+\n");//tampilkan pesan 
    printf("| %-12s |    %-3d   |   %s   |\n", heap->tasks[0].name, heap->tasks[0].priority, heap->tasks[0].isDone ? "Yes" : "No"); // Menampilkan informasi tentang tugas dengan prioritas tertinggi
    printf("+--------------+----------+-------+\n");//tampilkan pesan 
}


void markTaskAsDone(Heap* heap) {
    if (heap->size == 0) { // Memeriksa apakah heap kosong
        printf("No tasks to mark as done.\n"); // Menampilkan pesan bahwa tidak ada tugas yang dapat ditandai sebagai selesai
        return;
    }

    char taskName[50];
    printf("Enter task name to mark as done: "); getchar(); //tampilkan pesan 
    scanf("%[^\n]", taskName); getchar();

    int found = 0;
    int i;
    for (i = 0; i < heap->size; i++) { // Melakukan iterasi untuk mencari tugas dengan nama yang sesuai
        if (strcmp(heap->tasks[i].name, taskName) == 0) { // Membandingkan nama tugas dengan nama yang diinputkan
            found = 1; // Menandakan bahwa tugas ditemukan
            break;
        }
    }

    if (found) { // Jika tugas ditemukan
        heap->tasks[i].isDone = 1; // Menandai tugas sebagai selesai dengan mengatur isDone menjadi 1
        printf("Task marked as done successfully.\n"); // Menampilkan pesan bahwa tugas berhasil ditandai sebagai selesai
        
		printf("\nTask marked as done:\n");// Menampilkan pesan
    	printf("+--------------+----------+-------+\n");// Menampilkan pesan
    	printf("|     Name     | Priority | Done? |\n");// Menampilkan pesan
    	printf("+--------------+----------+-------+\n");// Menampilkan pesan
        	if (heap->tasks[i].isDone = 1) {
           	 printf("| %-12s |    %-3d   |   %s   |\n", heap->tasks[i].name, heap->tasks[i].priority, heap->tasks[i].isDone ? "Yes" : "No");
       	 	}
   		 printf("+--------------+----------+-------+\n");
    } else {
        printf("Task not found.\n"); // Menampilkan pesan bahwa tugas tidak ditemukan
    }
}


void printTasksToFile(Heap* heap) {
    if (heap->size == 0) { // Memeriksa apakah heap kosong
        printf("No tasks to print.\n"); // Menampilkan pesan bahwa tidak ada tugas yang dapat dicetak
        return;
    }

    FILE* file = fopen("tasks.txt", "w"); // Membuka file "tasks.txt" dalam mode tulis
    if (file == NULL) { // Memeriksa apakah file berhasil dibuka
        printf("Error opening file.\n"); // Menampilkan pesan kesalahan jika file gagal dibuka
        return;
    }

    for (int i = 0; i < heap->size; i++) { // Melakukan iterasi untuk mencetak tugas-tugas yang belum selesai ke dalam file
        if (!heap->tasks[i].isDone) { // Memeriksa apakah tugas belum selesai (isDone = 0)
            fprintf(file, "%s - Priority: %d\n", heap->tasks[i].name, heap->tasks[i].priority); // Menulis nama tugas dan prioritasnya ke dalam file
        }
    }

    fclose(file); // Menutup file setelah selesai mencetak
    printf("Tasks printed to file successfully.\n"); // Menampilkan pesan bahwa tugas-tugas berhasil dicetak ke dalam file
}

void listAllTasks(Heap* heap) {
    if (heap->size == 0) { // Memeriksa apakah heap kosong
        printf("No tasks to display.\n"); // Menampilkan pesan bahwa tidak ada tugas yang dapat ditampilkan
        return;
    }

    // Sorting the tasks based on priority
    for (int i = 0; i < heap->size - 1; i++) { // Algoritma pengurutan tugas berdasarkan prioritas
        for (int j = 0; j < heap->size - i - 1; j++) {
            if (heap->tasks[j].priority > heap->tasks[j + 1].priority) { // Jika prioritas tugas saat ini lebih besar dari prioritas tugas berikutnya, tukar posisi tugas
                swap(&heap->tasks[j], &heap->tasks[j + 1]);
            }
        }
    }

    printf("List of all tasks:\n");//tampilkan pesan 
    printf("+--------------+----------+-------+\n");//tampilkan pesan 
    printf("|     Name     | Priority | Done? |\n");//tampilkan pesan 
    printf("+--------------+----------+-------+\n");//tampilkan pesan 
    for (int i = 0; i < heap->size; i++) { // Melakukan iterasi untuk menampilkan semua tugas yang belum selesai
        if (!heap->tasks[i].isDone) { // Memeriksa apakah tugas belum selesai (isDone = 0)
            printf("| %-12s |    %-3d   |   %s   |\n", heap->tasks[i].name, heap->tasks[i].priority, heap->tasks[i].isDone ? "Yes" : "No"); // Menampilkan nama tugas, prioritas, dan status selesai ke layar
        }
    }
    printf("+--------------+----------+-------+\n"); //tampilkan pesan 
}


int main() { // Fungsi utama
    Heap heap; // heap
    initHeap(&heap); // Inisialisasi heap

    int choice; // pilihan berupa angka 
    do {
        printf("\nTask Priorities Manager\n"); printf("+---------------------+\n");//tampilkan pesan 
        printf("1. Add Task\n");//tampilkan pesan 
        printf("2. Remove Task\n");//tampilkan pesan 
        printf("3. Retrieve Highest Priority Task\n");//tampilkan pesan 
        printf("4. List All Tasks\n");//tampilkan pesan 
        printf("5. Mark Task as Done\n");//tampilkan pesan 
        printf("6. Print Tasks to File\n");//tampilkan pesan 
        printf("0. Exit\n");//tampilkan pesan 
        printf("Enter your choice: ");//tampilkan pesan 
        scanf("%d", &choice);

        switch (choice) { // Menjalankan pilihan sesuai input pengguna
            case 1:
                addTask(&heap); // Panggil fungsi addTask
                break;//menghentikan program supaya tidak looping 
            case 2:
                removeTask(&heap); // Panggil fungsi removeTask
                break;//menghentikan program supaya tidak looping 
            case 3:
                retrieveHighestPriorityTask(&heap); // Panggil fungsi retrieveHighestPriorityTask
                break;//menghentikan program supaya tidak looping 
            case 4:
                listAllTasks(&heap); // Panggil fungsi listAllTasks
                break;//menghentikan program supaya tidak looping 
            case 5:
                markTaskAsDone(&heap); // panggil fungsi markasdone
                break;//menghentikan program supaya tidak looping 
            case 6:
                printTasksToFile(&heap); // print file 
                break;//menghentikan program supaya tidak looping 
            case 0:
                printf("Exiting...\n"); //tampilkan pesan 
                break;//menghentikan program supaya tidak looping 
            default:
                printf("Invalid choice. Please try again.\n"); //tampilkan pesan
        }
    } while (choice != 0); // Ulangi loop hingga pengguna memilih keluar (pilihan 0)

    return 0;
}

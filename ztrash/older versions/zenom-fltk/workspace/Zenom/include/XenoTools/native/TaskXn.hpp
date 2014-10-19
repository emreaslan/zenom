//==============================================================================
// TaskXn.hpp - Native Task class.
//
// Author        : 
// Version       : 2.0.01 (Temmuz 2009)
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _TASKXN_HPP_INCLUDED
#define _TASKXN_HPP_INCLUDED

#include <native/task.h>


//==============================================================================
// class TaskXn
//------------------------------------------------------------------------------
// \brief
// Task objects.
// TaskXn sınıfı çalıştırılmak istenen fonksiyon belirtilerek veya sınıf 
// içersindeki run fonksiyonunu implement edilerek kullanılır. Round-robin ve 
// öncelik tabanlı FIFO scheduler destekler. Task objesini periyodik şekilde
// çalıştırabilir ve taskların birbirlerine mesaj gönderme olanağı da vardır.
// 
// <b>Example Program:</b>
//
// \include TaskXn.t.cpp
//==============================================================================

#define TASK_TIMEOUT 10000000000LL  // Varsayilan zaman asimi olarak 10sn
#define TASK_MODE_C    T_JOINABLE      // Varsayilan yarailma modu
#define TASK_PRIO    50
#define TASK_STACK_SIZE  0

class TaskXn
{
 public:

   // Sadece objenin degiskenlerine atamalar yapilir.
   TaskXn();
   
   // Task yaratan ise delete, task'a baglanan ise unbind edilir.
   ~TaskXn();
  
   // Task yaratir.
   //  name     Yaratilacak Task ismi
   //  stksize  Task icin stack boyutu
   //           Sıfır girilirse, önceden tanımlanmış uygun bir değer verilir.
   //  TASK_PRIO     Task'in onceligi [1 .. 99] ( 1 En dusuk )
   //  TASK_MODE_C     Task yaratılma modu
   //           T_FPU    FPU musait olduğuna kullanmasına izin verir.
   //           T_SUSP   Durdurulmuş taskı devam ettirir.
   //           T_CPU(cpuid)  Taskı geçerli cpuda çalıştırır.
   //           T_JOINABLE    Bir taskın başka bir taskın sonlanmasına kadar
   //                         beklemesini sağlar
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int create(const char *name = NULL, int stksize = TASK_STACK_SIZE, int prio = TASK_PRIO, int mode = TASK_MODE_C); 

   // Task'a baglanir.
   //  name      Baglanilacak Task ismi
   //  TASK_TIMEOUT  Baglanmak icin beklenecek clock tick sayisi
   //           Varsayilan olarak, sonsuza kada bekler
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int bind(const char *name, RTIME timeout = TASK_TIMEOUT); 

   // Task'i baslatir.
   //  void(*entry)(void *cookie)   Task'in isleyecegi fonksiyon pointeri
   //  cookie      Task'a isleyecegi fonksiyona gidecek argumanlar    
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int start(void(*entry)(void *cookie), void *cookie);

   // Task'i baslatir.
   // Bu fonksiyon run fonksiyonu override edilmisse kullanilmalidir
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int start();


   // Task'i askiya alir.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int suspend(); 

   // Task'a kaldigi yerden devam eder.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int resume(); 


   // Manual round-robin
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int yield(); 

   // Task'ın çalışacağı periyodik zamanı ayarlar.
   //  idate     Periyodik zamanının başlama zamanı. Task bu zaman dolana kadar
   //            durur.(clock ticks)
   //            TM_NOW   Durdurma olmadan başlar.
   //  period    Taskın çalışcağı periyod(clock ticks)
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int setPeriodic(RTIME idate, RTIME period); 

   // Ayarlanan periyod zamanı bitene kadar bekler.
   //  overruns_r Overrun sayisi
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int waitPeriod(unsigned long* overruns_r = NULL); 

   // Task'in onceligini degistirir
   //  TASK_PRIO      Task'in onceligi [1 .. 99] ( 1 En dusuk )
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int setPriority( int prio ); 

   // Task'i herhangi bir bekleme aninda cikartir, calismaya devam ettirir. 
   // Ancak suspend edilen task calismaya devam etmez.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int unblock(); 

   // Su anki task'i getirir.
   //  return 	Basarili olursa task aciklayiciyi getirir.
   //          	getErrnoError() fonksiyonu ile ulasılabilir
   RT_TASK* self(); 

   // Task'in round-robin quantumunu degistirir.
   //  quantum  The round-robin quantum
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int slice(RTIME quantum);

   // Task'a mesaj gonderilir.
   //  receiver Mesaj gonderilecek Task
   //  mcb_s    Gonderilecek mesaj
   //  mcb_r    Alicidan gelen cevap
   //           NULL ise cevap ihmal edilir
   //  TASK_TIMEOUT  Cevap mesaji icin beklenecek clock tick sayisi
   //  return 	Basarili ise receiver'dan gelen cevap mesajinin boyutunu dondurur,
   //           Hata meydana gelirse -1 getirir, hata degerine getErrnoError()
   //           fonksiyonu ile ulasılabilir
   int send( TaskXn receiver, RT_TASK_MCB * mcb_s, RT_TASK_MCB* mcb_r = NULL, RTIME timeout = TASK_TIMEOUT );

   // Task'a gonderilen mesaj alinir.
   //  mcb_r    Task'dan gelen mesaj
   //  TASK_TIMEOUT  Mesaj icin beklenecek clock tick sayisi
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int receive( RT_TASK_MCB* mcb_r, RTIME timeout = TASK_TIMEOUT );

   // Task'a cevap verilir.
   //  mcb_s    Task'a cevap mesajı
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int reply( RT_TASK_MCB* mcb_s = NULL);


   // Task yaratir ve hemen baslatir.
   //  name      Yaratilacak Task ismi
   //  stksize   Task icin stack boyutu
   //  TASK_PRIO      Task'in onceligi [1 .. 99] ( 1 En dusuk )
   //  TASK_MODE_C      Task yaratilma modu    
   //  void(*entry)(void *cookie)   Task'in isleyecegi fonksiyon pointeri
   //  cookie      Task'a isleyecegi fonksiyona gidecek argumanlar   
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int spawn(const char * name, int stksize, int prio, int mode, void(*entry)(void *cookie), void * cookie );

   // Linux taskini native Xenomai taska cevirir.
   //  name     Task ismi
   //  TASK_PRIO     Task'in onceligi [1 .. 99] ( 1 En dusuk )
   //  TASK_MODE_C     Task yaratilma modu    
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int shadow(const char * name, int prio, int mode);

   // Task gorevini bitirine kadar bekler.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int join();

   // Task'i siler. Ancak task yaratan (create) eden
   // obje silebilir. Aksi takdirde -1 getirir ve EACCES hatasi d_errno degiskenine
   // atanir.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int deleteTask();

   // Task'i serbest birakir. Ancak task'e baglanan
   // (bind) obje serbest birakabilir. Aksi takdirde -1 getirir ve EACCES hatasi 
   // d_errno degiskenine atanir.
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
   int unbind();

   // Task bilgilerini info struct icine yazar.
   //  info	Task bilgilerinin yazilacagi struct pointeri  
   //  return 	Basarili olursa 0 , Hata meydana gelirse -1 getirir, 
   //           hata degerine getErrnoError() fonksiyonu ile ulasılabilir
  int inquire( RT_TASK_INFO * info );


   //  return  En son meydana gelen hatayi getirir.
  inline int getErrnoError() const;
 
  //  Task'in calismaya baslayayinca calistiracagi fonksiyon
  //  Bu fonksiyon, Task objesinden bir obje olusturuldugunda override edilmedir
  //  Bu fonksiyon ici bos sekilde yazilmistir, kullanici icini override ederek
  //   doldurmalidir
  virtual void run(){}  
  
 private:
 
  // Xenomai task bu fonksiyonu calistiracak
  static void taskRun(void *classPtr)
  {
    TaskXn *ptr = (TaskXn*) classPtr;
    ptr->run();
    
    return ;
  }
 

   // Task 
  RT_TASK task;

   // Task ismi
  char *taskName;

   // Reply fonksiyonu icin receive fonksiyonundan gelen deger 
  int flowid;
   
   // Task yaratan( create ) eden obje ise true, 
   // Task'a baglanan obje ise false;
  bool isOwner;
  
   // Hatalarin saklandigi degisken
  int d_errno;
  
  //  Objenin Spawn islemi ile uretilme bilgisini tutar 
  bool isSpawn;
};


//==============================================================================
// TaskXn::getErrnoError
//==============================================================================
int TaskXn::getErrnoError() const
{
 return d_errno;
}

#endif // _TASKXN_HPP_INCLUDED

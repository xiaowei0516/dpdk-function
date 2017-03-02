#ifndef __SPIN_LOCK__
#define __SPIN_LOCK__

typedef struct {
    volatile int locked; /**< lock status 0 = unlocked, 1 = locked */
} rte_spinlock_t;

void rte_pause(){
	;
}

//spinlock的初始化，lock=0，标识无锁状态
static inline void
rte_spinlock_init(rte_spinlock_t *sl)
{
    sl->locked = 0;
}

//加锁，也就是locked置1
static inline void
rte_spinlock_lock(rte_spinlock_t *sl)
{
    while (__sync_lock_test_and_set(&sl->locked, 1))
        while(sl->locked)
            rte_pause();
}

//解锁
static inline void
rte_spinlock_unlock (rte_spinlock_t *sl)
{
    __sync_lock_release(&sl->locked);
}

// 尝试加锁，如果当前状态是无锁，func返回1，标识加锁成功，失败func返回0
static inline int
rte_spinlock_trylock (rte_spinlock_t *sl)
{
    return (__sync_lock_test_and_set(&sl->locked,1) == 0);
}

//返回当前锁的status
static inline int rte_spinlock_is_locked (rte_spinlock_t *sl)
{
    return sl->locked;
}

#endif

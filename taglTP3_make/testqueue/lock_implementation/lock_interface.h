#ifndef _LOCK_INTERFACE_H
#define _LOCK_INTERFACE_H

void lock_init(void);
void lock_finalize(void);


void lock_lock(void);
void lock_unlock(void);

#endif

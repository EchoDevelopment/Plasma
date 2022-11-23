#pragma once

void irq_remap();
void eoi(char intv);
void irq_set_mask(char vec);
void irq_clear_mask(char vec);
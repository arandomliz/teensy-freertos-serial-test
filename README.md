# freeRTOS UART SPI test
It seems like that UART isn't able to send anything when using it in combination with
`tsandmann/freertos-teensy` and SPI.

The project has a few targets, in order to try and show the error namely:
```
without_freertos  # run test without freertos to show that it could work
freertos_spi  # SPI only
freertos_uart  # uart only
freertos_spi_uart  # SPI and UART together
```

The last target `freertos_spi_uart` is the one that doesn't reach the `Done all`
print statement.

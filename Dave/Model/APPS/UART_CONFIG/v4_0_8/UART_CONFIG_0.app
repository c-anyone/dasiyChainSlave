<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="UART_CONFIG" URI="http://resources/4.0.8/app/UART_CONFIG/0" description="Configures the USIC peripheral to work for the UART protocol." mode="NOTSHARABLE" version="4.0.8" minDaveVersion="4.1.2" instanceLabel="UART_DAISY" appLabel="">
  <properties provideInit="true"/>
  <virtualSignals name="rxd" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_dx0ins" hwSignal="dx0ins" hwResource="//@hwResources.0" visible="true">
    <upwardMapList xsi:type="ResourceModel:Connections" href="../../DIGITAL_IO/v4_0_14/DIGITAL_IO_3.app#//@connections.2"/>
  </virtualSignals>
  <virtualSignals name="dx1ins" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_dx1ins" hwSignal="dx1ins" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="dx1ins_out" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_dx1ins_sys_out" hwSignal="dx1ins" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="tx_data_validation" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_dx2ins" hwSignal="dx2ins" hwResource="//@hwResources.0" required="false"/>
  <virtualSignals name="dx2ins_out" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_dx2ins_sys_out" hwSignal="dx2ins" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="txd" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_dout0" hwSignal="dout0" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="transmit_buffer_event" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_standard_tx_event" hwSignal="transmit_buffer_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="standard_receive_event" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_standard_rx_event" hwSignal="standard_receive_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="transmit_shift_event" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_tx_shift_event" hwSignal="transmit_shift_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="receive_start_event" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_rx_start_event" hwSignal="receive_start_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="alternate_receive_event" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_alt_rx_event" hwSignal="alternate_receive_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="protocol_specific_event" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_proto_specfic_event" hwSignal="protocol_specific_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="fifo_standard_transmit_buffer_event" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_fifo_tx_event" hwSignal="standard_transmit_buffer_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="fifo_transmit_buffer_error_event" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_fifo_tx_err_event" hwSignal="transmit_buffer_error_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="fifo_standard_receive_buffer_event" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_fifo_rx_event" hwSignal="standard_receive_buffer_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="fifo_receive_buffer_error_event" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_fifo_rx_err_event" hwSignal="receive_buffer_error_int" hwResource="//@hwResources.0" visible="true"/>
  <virtualSignals name="fifo_alternate_receive_buffer_event" URI="http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_fifo_alt_rx_event" hwSignal="alternate_receive_buffer_int" hwResource="//@hwResources.0" visible="true"/>
  <requiredApps URI="http://resources/4.0.8/app/UART_CONFIG/0/ra_clock" requiredAppName="CLOCK_XMC1" requiringMode="SHARABLE">
    <downwardMapList xsi:type="ResourceModel:App" href="../../CLOCK_XMC1/v4_0_14/CLOCK_XMC1_0.app#/"/>
  </requiredApps>
  <hwResources name="Channel" URI="http://resources/4.0.8/app/UART_CONFIG/0/hwres_usic_channel" resourceGroupUri="peripheral/usic/*/channel/*" mResGrpUri="peripheral/usic/*/channel/*">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/USIC0/USIC0_0.dd#//@provided.43"/>
  </hwResources>
  <connections URI="http://resources/4.0.8/app/UART_CONFIG/0/http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_dout0/http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_dx0ins" systemDefined="true" sourceSignal="txd" targetSignal="rxd" required="false" srcVirtualSignal="//@virtualSignals.5" targetVirtualSignal="//@virtualSignals.0"/>
  <connections URI="http://resources/4.0.8/app/UART_CONFIG/0/http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_dout0/http://resources/4.0.14/app/DIGITAL_IO/2/vs_digital_io_pad_pin" sourceSignal="txd" targetSignal="pin" srcVirtualSignal="//@virtualSignals.5">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../DIGITAL_IO/v4_0_14/DIGITAL_IO_2.app#//@virtualSignals.1"/>
    <targetVirtualSignal href="../../DIGITAL_IO/v4_0_14/DIGITAL_IO_2.app#//@virtualSignals.1"/>
  </connections>
  <connections URI="http://resources/4.0.8/app/UART_CONFIG/0/http://resources/4.0.8/app/UART_CONFIG/0/vs_uart_fifo_rx_event/http://resources/4.0.8/app/INTERRUPT/0/vs_nvic_signal_in" sourceSignal="fifo_standard_receive_buffer_event" targetSignal="sr_irq" srcVirtualSignal="//@virtualSignals.14">
    <downwardMapList xsi:type="ResourceModel:VirtualSignal" href="../../INTERRUPT/v4_0_8/INTERRUPT_0.app#//@virtualSignals.0"/>
    <targetVirtualSignal href="../../INTERRUPT/v4_0_8/INTERRUPT_0.app#//@virtualSignals.0"/>
  </connections>
</ResourceModel:App>

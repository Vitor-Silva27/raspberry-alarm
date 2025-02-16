# 🚨 Raspberry Alarm  

O **Raspberry Alarm** é um sistema de alarme de segurança desenvolvido durante o programa *Embarcatech*, utilizando o **Raspberry Pi Pico W** embarcado na placa **BitDogLab**. O sistema monitora níveis de ruído em um ambiente e, ao detectar sons excessivos, aciona um alarme sonoro (buzzer) e visual (LED). Ele utiliza um **microfone analógico** para captar os sons e um **algoritmo de detecção de picos de ruído** para identificar possíveis intrusos. O alarme pode ser desativado manualmente por meio de um botão físico.  

## 🚀 Funcionalidades  

- 🔊 **Detecção de Ruído:** Monitora o ambiente em tempo real usando um microfone analógico.  
- 🚨 **Ativação do Alarme:** Quando o ruído ultrapassa um limite predefinido (`MIN_NOISE`), o alarme é acionado.  
- 🔴 **Sinalização Visual e Sonora:** O LED vermelho começa a piscar e o buzzer emite sons intermitentes.  
- 🖥️ **Notificações no Monitor Serial:** O alerta "ALERTA DE INTRUSO!!!" é exibido no monitor serial.  
- 🛑 **Desativação Manual:** O alarme pode ser desligado pressionando um botão físico.  

## ⚙️ Como Funciona  

1. **Inicialização:** Configura os pinos do LED, microfone, buzzer e botão.  
2. **Leitura do Microfone:** O microfone é amostrado em intervalos regulares, armazenando os valores de ruído.  
3. **Detecção de Ruído:** O sistema analisa os picos de ruído e, se um valor acima de `MIN_NOISE` for detectado, ativa o alarme.  
4. **Ativação do Alarme:**  
   - O **buzzer** emite um alerta sonoro.  
   - O **LED vermelho** começa a piscar.  
   - O alerta **"ALERTA DE INTRUSO!!!"** é impresso no monitor serial.  
5. **Desativação do Alarme:** O botão físico interrompe o alarme e restaura o sistema ao estado de monitoramento.  

Desenvolvido por [vitor silva](https://github.com/Vitor-Silva27) 🚀
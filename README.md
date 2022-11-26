# Sistema de Irrigação Automático :cloud_with_rain:
Projeto de desenvolvimento de um Sistema de Irrigação Automático, com o objetivo de automatizar o processo de irrigação de pequenas áreas. **Desenvolvedores:** Cassiano Prediger, Roni Eduardo Peroni e Marco Antônio Andrade, acadêmicos do curso de Sistemas de Informação da Universidade Unimater de Pato Branco (PR) :nerd_face:
<div align=center>
 <a href="https://github.com/MarcoAndradee">
  <img height="200em" src="https://media1.giphy.com/media/VwjRf92moBypy4Sqwd/giphy.gif?cid=ecf05e47myg3v9g531b2d6owy51gkdydj9ck64ntsxew2ad1&rid=giphy.gif&ct=g">
</div>


  
# Componentes utilizados no desenvolvimento:
:black_circle: **NodeMCU ESP8266** - É uma placa de desenvolvimento que combina o chip ESP8266, uma interface usb-serial e um regulador de tensão 3.3V. A programação pode ser feita usando LUA ou a IDE do Arduino, utilizando a comunicação via cabo micro-usb. A seguir temos uma imagem da placa:
<div align=center>
 <a href="https://github.com/MarcoAndradee">
  <img height="200em" src="https://curtocircuito.com.br/pub/media/catalog/product/cache/ebf77fb58d795a2dbe3218c301c821c6/n/o/nodemcu_v3_-_esp8266_-_ch340_1.jpg">
</div>

:black_circle: **Relé 3V** - O módulo relé 3V é um componente eletrônico utilizado para acionar e desacionar cargas. O seu funcionamento é simples. Quando uma corrente circula pela bobina do relé, ele gera um campo eletromagnético que atrai o contato para fechar o circuito. Na imagem a seguir é possível identificar o modelo do módulo relé 3V:
<div align=center>
 <a href="https://github.com/MarcoAndradee">
  <img height="200em" src="https://http2.mlstatic.com/D_NQ_NP_890118-MLB49577081365_042022-W.jpg">
</div>

:black_circle: **Válvula Solenoide para Água** - Trata-se de um mecanismo eletrônico que pode ser aplicado em diversos projetos, essa válvula possui internamente uma bobina em formato cilíndrico e posicionamento de 180º em relação a entrada e saída de água. A seguir temos uma imagem do solenoide:
<div align=center>
 <a href="https://github.com/MarcoAndradee">
  <img height="200em" src="https://images.tcdn.com.br/img/img_prod/679014/valvula_solenoide_de_agua_emicol_127v_4485_1_26266f28524dd3a1c30d14b683eba9fb.jpg">
</div>

:black_circle: **Sensor de Temperatura e Umidade DHT11** - O sensor DHT11 é um sensor de temperatura e umidade com uma sinal digital em sua saída. Sua tecnologia garante excelente estabilidade e confiabilidade. Um microcontrolador de alta performance de 8 bits garante isto no encapsulamento do módulo. Este sensor inclui um elemento resistivo do tipo NTC que faz a medição da temperatura. Possui excelente qualidade, resposta rápida, habilidade de anti-interferência e vantagens antes só encontradas em dispositivos de alto custo. Na imagem a seguir é possível identificar o modelo do sensor:
<div align=center>
 <a href="https://github.com/MarcoAndradee">
  <img height="200em" src="https://www.diversoeletronica.com.br/loja/img/prod/img00_como_usar_com_arduino_modulo_sensor_de_umidade_e_temperatura_dht11_uno_mega_2560_nan.png">
</div>

:black_circle: **Sensor de Umidade do solo YL-69 com módulo** - Este sensor foi feito para detectar as variações de umidade no solo, sendo que quando o solo está seco a saída do sensor fica em estado alto, e quando úmido em estado baixo. O limite entre seco e úmido pode ser ajustado através do potenciômetro presente no sensor que regulará a saída digital D0. Contudo para ter uma resolução melhor é possível utilizar a saída analógica A0 e conectar a um conversor AD, como por exemplo a existente no Arduino. Na imagem a seguir é possível identificar o modelo do sensor:
<div align=center>
 <a href="https://github.com/MarcoAndradee">
  <img height="200em" src="https://cdn.awsli.com.br/600x700/468/468162/produto/19414371/1ceaf2d245.jpg">
</div>

# Como funciona:
<div align=center>
 <a href="https://github.com/MarcoAndradee">
 <img height="200em" src="./Servidor Web/assets/img/WebServer.gif">
</div>

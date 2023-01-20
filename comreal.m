clc%
clear%
close all%

%% variables
global dato
dato = 0; %inicializar variable dato
%% leer y configurar puerto serial
%4resetea todo los puertos
instrreset
%configura el puerto serial
tivaCom = serial('COM3', 'BaudRate', 9600);
%indica el no. de bits de la cadena de datos
tivaCom.BytesAvailableFcnCount = 8;

%abre el puerto serial
fopen(tivaCom);
%cada que los bytes de entrada estén listos llamamos a la función
%LeerPuertoSerial
tivaCom.BytesAvailableFcn = @LeerPuertoSerial; %@indica un callback

%% imprimir los datos del puerto serial y graficar
%% para graficar
%variables para la grafica
i=1; %cont de num de muestras 
v = zeros; %v de ceros, para poder graficar datos
vector(1:149)= v;
%%obtenemos la señal en el dom de frecuencias
signal_DFT = fft(vector); %fast fourir transform, calcula la DFT de la señal usando el algoritmo FFT

while true
     %cuando en el puerto serial exista la letra 'E'
     %cierra el ciclo while
     if char(dato(i)) == 'E'
         break
     elseif mod(i,150) == 0
         
         v(i) = dato(i);
         subplot(2,1,1);
         xlim([i i+150]);
         ylim([0 5.1]);
         title(sprintf('Señal'))
         xlabel('Tiempo(s)');
         ylabel('voltaje(v)');
         grid on
         plot(v, 'm');
         drawnow %muestra actualizaciones despues de añadir puntos
         dato;
         i = i+150;
         
         
         %% graficamos el espectro de potencias
       
    subplot(2,1,2)
    stem((abs(signal_DFT)).^2, 'm');
    grid on
    xlabel('Muestras')
    xlabel('Amplitud (u.a.)')
    title('Espectro de potencias')
    xlim([i i+150]);
    ylim([0 5.1]);
    drawnow
    i=1;
    
     else 
         v(i) = dato(1);
         
         subplot(2,1,1);
         grid on
         title(sprintf('señal'))
         xlabel('Tiempo(S)');
         ylabel('Voltaje(v)');
         xlim([i i+150]);
         ylim([0 5.1]);
         plot(v,'m');
         drawnow 
         dato;
         
         subplot(2,1,2)
         stem((abs(signal_DFT)).^2,'m');
         xlabel('Muestras')
         ylabel('Amplitud(ua)')
         title('espectro pot')
         xlim([i i+150]);
         ylim([0 5.1]);
         grid on 
         drawnow
     end
      i = i+1;
end
%cierra el puerto serial
fclose(tivaCom);
         
         
       



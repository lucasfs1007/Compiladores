program ConversaoTemperaturas;

var
    EscalaOrigem, EscalaDestino: Char;
    TemperaturaOrigem, TemperaturaDestino: Real;

begin
    // Leitura das entradas
    readln(EscalaOrigem);
    readln(EscalaDestino);
    readln(TemperaturaOrigem);

    // Conversão das temperaturas
    case EscalaOrigem of
        'C': begin
                case EscalaDestino of
                    'F': TemperaturaDestino := (TemperaturaOrigem * 9/5) + 32;
                    'K': TemperaturaDestino := TemperaturaOrigem + 273.15;
                end;
            end;
        'F': begin
                case EscalaDestino of
                    'C': TemperaturaDestino := (TemperaturaOrigem - 32) * 5/9;
                    'K': TemperaturaDestino := (TemperaturaOrigem + 459.67) * 5/9;
                end;
            end;
        'K': begin
                case EscalaDestino of
                    'C': TemperaturaDestino := TemperaturaOrigem - 273.15;
                    'F': TemperaturaDestino := TemperaturaOrigem * 9/5 - 459.67;
                end;
            end;
    end;

    // Saída da temperatura convertida
    writeln(TemperaturaDestino:0:2);
end.


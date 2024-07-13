program SomaN;
var
  N, i, X, Soma: LongInt;
begin

  Soma := 0;


  ReadLn(N);

 
  for i := 1 to N do
  begin
    ReadLn(X);
    Soma := Soma + X;
  end;


  WriteLn(Soma);
end.


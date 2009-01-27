--Triggers

drop trigger trigger_log_client;
drop trigger trigger_log_circuit;
drop trigger trigger_log_hotel;
drop trigger trigger_log_destination;
				

create or replace trigger trigger_log_client
before delete or update or insert on Client
begin  
if DELETING 
then	
   insert into LOG values(sysdate,USER,'DELETE','Client');
  
   else if UPDATING
     then 
     	  insert into LOG values(sysdate,USER,'UPDATE','Client');
     else
	  insert into LOG values(sysdate,USER,'INSERT','Client');	
	  end if;
end if;


end;
/

create or replace trigger trigger_log_circuit
before delete or update or insert on Circuit
begin  
if DELETING 
then	
   insert into LOG values(sysdate,USER,'DELETE','Circuit');
  
   else if UPDATING
     then 
     	  insert into LOG values(sysdate,USER,'UPDATE','Circuit');
     else
	  insert into LOG values(sysdate,USER,'INSERT','Circuit');	
	  end if;
end if;


end;
/

create or replace trigger trigger_log_hotel
before delete or update or insert on Hotel
begin  
if DELETING 
then	
   insert into LOG values(sysdate,USER,'DELETE','Hotel');
  
   else if UPDATING
     then 
     	  insert into LOG values(sysdate,USER,'UPDATE','Hotel');
     else
	  insert into LOG values(sysdate,USER,'INSERT','Hotel');	
	  end if;
end if;


end;
/

create or replace trigger trigger_log_destination
before delete or update or insert on Destination
begin  
if DELETING 
then	
   insert into LOG values(sysdate,USER,'DELETE','Destination');
  
   else if UPDATING
     then 
     	  insert into LOG values(sysdate,USER,'UPDATE','Destination');
     else
	  insert into LOG values(sysdate,USER,'INSERT','Destination');	
	  end if;
end if;


end;
/


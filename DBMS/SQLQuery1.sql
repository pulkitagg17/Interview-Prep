
--Creating Employee Table

--create table Employees(
--	employeeID int primary key,
--	firstName varchar(50),
--	lastName varchar(50),
--	departmentID int,
--	salary decimal(10,2),
--	hireDate date,
--	managerID int,
--	status varchar(20) 
--);

-- Departments Table
--create table Departments(
--	departmentID int primary key,
--	departmentName varchar(50),
--	budget decimal(10,2)
--);

---- Projects Table
--create table Projects(
--	projectID int primary key,
--	projectName varchar(100),
--	departmentID int,
--	startDate date,
--	endDate date,
--	budget decimal(10,2)
--);

---- EmployeeProject Table (Many-to-Many Relationship)
--create table EmployeeProject(
--	employeeID int,
--	projectID int,
--	role varchar(50),
--	foreign key (employeeID) references Employees(employeeID),
--	foreign key (projectID) references Projects(projectID)
--);

---- Salaries Table
--create table Salaries (
--employeeID INT,
--salary DECIMAL(10, 2),
--startDate DATE,
--endDate DATE,
--FOREIGN KEY (employeeID) REFERENCES Employees(employeeID)
--);

---- Attendance Table
--create table Attendance (
--employeeID INT,
--date DATE,
--status VARCHAR(20), -- 'Present', 'Absent', 'Leave'
--FOREIGN KEY (employeeID) REFERENCES Employees(employeeID)
--);

--BASIC QUESTIONS

--1.
--select E.firstName, E.lastName
--from EmployeeProject EP
--join Employees E on EP.employeeID = E.employeeID
--group by E.firstName, E.lastName
--having count(EP.projectID) > 2;

--2.
--select E.firstName, D.departmentID
--from Employees E
--join Departments D on E.departmentID = D.departmentID
--left join EmployeeProject EP on E.employeeID = EP.employeeID
--where projectID is null

--3.
--select employeeID, firstName, lastName, hireDate
--from Employees
--where datepart(weekday, hireDate) in (1,7);

--4.
--select employeeID, firstName, lastName, hireDate
--from Employees
--where 
--	status = 'Active' 
--	and 
--	hireDate <= dateadd(year, -5, getdate());

--5.
--select P.*
--from Projects P
--join Departments D on D.departmentID = P.departmentID
--where P.budget <= 100000;

--6.
--select E.*, D.departmentName, EP.role
--from Employees E
--join Departments D on D.departmentID = E.departmentID
--left join EmployeeProject EP on EP.employeeID = E.employeeID;

--7.
--select E.firstName, E.lastName
--from Employees E
--join Departments D on D.departmentID = E.departmentID
--where d.departmentName = 'IT'
--and E.salary > (
--				select 
--					avg(E2.salary)
--				from 
--					Employees E2
--				where
--					E2.departmentID = D.departmentID
--);

--8.
--select E.firstName, E.lastName, E.hireDate, D.departmentName,
--	   M.firstName as managerFirstName,
--	   M.lastName as managerLastName
--from Employees E
--join
--	Departments D on E.departmentID = D.departmentID
--left join
--	Employees M on E.managerID = M.employeeID
--where 
--	YEAR(E.hireDate) = 2023;

--9.
--select D.departmentName, D.budget, count(E.employeeID) as totalEmp
--from Departments D
--left join
--	Employees E on D.departmentID = E.employeeID
--group by
--	D.departmentName, D.budget;

--10.
--SELECT *
--FROM Employees
--WHERE salary >= (
--    SELECT PERCENTILE_CONT(0.9) WITHIN GROUP (ORDER BY salary) 
--    OVER ()
--);

--Filtering Data
--1.
--select *
--from Employees
--where salary >= (
-- select PERCENTILE_CONT(0.9) within group (order by salary) over());

--2.
--select E.firstName, E.lastName
--from Employees E
--join EmployeeProject EP on EP.employeeID = E.employeeID
--where EP.role like '%Developer%';

--3.
--select P.*
--from Projects P
--left join EmployeeProject EP on P.projectID = EP.projectID
--where EP.employeeID is null;

--4.
--select E.employeeID, E.firstName, E.lastName,
----showing avg salary as in new column
--(select avg(E2.salary)
--	from Employees E2
--	where E2.departmentID = E.departmentID)  as depAvg
---- end
--from Employees E
--where E.salary <= (
--	select avg(E2.salary)
--	from Employees E2
--	where E2.departmentID = E.departmentID
--);

--5.
--select E.firstName, E.lastName, E.hireDate
--from Employees E
--left join EmployeeProject EP on E.employeeID = EP.employeeID
--where EP.projectID is null 
--and E.hireDate >= DATEADD(month , -6, getdate());

--6.
--select E.firstName, E.lastName, E.employeeID, E.salary
--from Employees E
--join EmployeeProject EP on E.employeeID = EP.employeeID
--where E.salary between 60000 and 120000
--group by E.employeeID, E.firstName, E.lastName, E.salary
--having count(distinct EP.projectID) > 1;

--7.
--select E.employeeID, E.firstName, E.lastName, E.departmentID,
--E.status
--from Employees E
--join Departments D on E.departmentID = D.departmentID
--where D.budget > 80000
--and E.hireDate < '2022-01-01'
--and E.status = 'Active';

--8.
--select E.employeeID, E.firstName, E.lastName, E.departmentID
--from Employees E
--join Departments D on E.departmentID = D.departmentID
--join Projects P on D.departmentID = P.departmentID
--where (D.departmentName = 'HR' or D.departmentName = 'Finance')
--and P.startDate >= '2022-01-01';

--9.
--select E.firstName, E.lastName, E.employeeID, E.salary
--from Employees E
--left join EmployeeProject EP on E.employeeID = EP.employeeID
--where EP.projectID is null
--and E.salary <(
--	select avg(E2.salary)
--	from Employees E2
--);

--10.
--select E.firstName, E.lastName, E.hireDate
--from Employees E
--where E.lastName like 'J%'
--and E.hireDate >= '2020-01-01';

--SORTING DATA
--1.
--select top 3 P.*
--from Projects P
--order by P.budget desc;

--2.
--select E.*
--from Employees E
--order by
--	case when E.status = 'Active' then 0 else 1 end,
--	E.lastName asc;

--3.
--select 
--	D.departmentID,
--	D.departmentName,
--	count(E.employeeID) as employeeCount
--from Departments D
--left join Employees E on D.departmentID = E.departmentID
--group by D.departmentID, D.departmentName
--order by employeeCount desc;

--4.
--select E.*
--from Employees E
--order by E.salary desc, E.hireDate asc;

--5.
--select D.departmentID, D.departmentName, D.budget,
--	count(E.employeeID) as employeeCnt
--from Departments D
--left join Employees E on D.departmentID = E.departmentID
--group by D.departmentID, D.departmentName, D.budget
--order by D.budget asc;

--6
--select E.firstName, E.lastName, E.employeeID, 
--	E.hireDate, D.departmentName
--from Employees E
--left join Departments D on E.departmentID = D.departmentID
--order by D.departmentName asc, E.hireDate asc;

--7.
--select P.*
--from Projects P
--order by
--	case when P.endDate is null then 0 else 1 end,
--    P.startDate asc;

--8.
--select E.firstName, E.lastName, E.employeeID, EP.role
--from Employees E
--left join EmployeeProject EP on E.employeeID = EP.employeeID
--order by E.firstName asc;


--AGGREGATING DATA
--1.
--select EP.employeeID,
--count(EP.projectID) as totalProject
--from EmployeeProject EP
--group by EP.employeeID
--having count(EP.projectID) > 2

--2.
--select E.departmentID, D.departmentName,
--	avg(E.salary) as averageSalary

--from Employees E
--join Departments D on D.departmentID = E.departmentID
--group by E.departmentID, D.departmentName 
--having avg(E.salary) > 6000

--3.
--select D.departmentID, D.departmentName,
--	avg(P.budget) as Average,
--	min(P.budget) as Minimum,
--	max(P.budget) as Maximum
--from Departments D
--join Projects P on D.departmentID = P.departmentID
--group by D.departmentID, D.departmentName

--4.
--select D.departmentID, D.departmentName,
--	sum(E.salary) as TotalSalary
--from Departments D
--join Employees E on E.departmentID = D.departmentID
--group by D.departmentID, D.departmentName

--5.
--select 
--	year(hireDate) as hireYear,
--	count(*) as empCnt
--from Employees
--group by year(hireDate)
--order by hireYear asc;

--6.
--select D.departmentName,
--	avg(E.salary) as AverageSalary
--from Departments D
--join Employees E on E.departmentID = D.departmentID
--group by departmentName
--having avg(E.salary) >=(
--	select avg(salary) from Employees
--);

--7.
--select D.departmentName,
--	sum(S.salary) as totalSalary
--from Departments D
--join Employees E on E.departmentID = D.departmentID
--join Salaries S on S.employeeID = E.employeeID
--where E.employeeID in (
--	select employeeID
--	from Salaries
--	group by employeeID
--	having count(*) > 1
--)

--group by D.departmentName;

--8.
--select D.departmentName,
--	count(distinct E.employeeID) as TotalNumber
--from Departments D
--left join Employees E on E.departmentID = D.departmentID
--left join EmployeeProject EP on EP.employeeID = E.employeeID
--where EP.projectID is not null
--group by D.departmentName;

--9.
--select D.departmentName, E.firstName, E.lastName, 'Max' as SalaryType
--from Employees E
--join Departments D on D.departmentID = E.departmentID
--where E.salary = (
--	select max(E2.salary)
--	from Employees E2
--	where E2.departmentID = E.departmentID
--)

--union all

--select D.departmentName, E.firstName, E.lastName, 'Min' as SalaryType
--from Employees E
--join Departments D on D.departmentID = E.departmentID
--where E.salary = (
--	select min(E2.salary)
--	from Employees E2
--	where E2.departmentID = E.departmentID
--);

--10.
--select D.departmentName,
--D.budget as departmentBudget,
--isnull(sum(P.budget),0) as total_bud,
--D.budget - isnull(sum(P.budget),0) as remaining_budget
--from Departments D
--left join Projects P on D.departmentID = P.departmentID
--where D.departmentName = 'IT'
--group by D.departmentName, D.budget;

--JOINS
--1.
--select E.firstName, E.lastName,
--P.projectName as ProjectName,
--EP.projectID as ProjectIDs --just for reference
--from Employees E
--left join EmployeeProject EP on E.employeeID = EP.employeeID
--left join Projects P on EP.projectID = P.projectID

--2.
--select P.projectID, P.projectName,
--	count(EP.employeeID) as totalNumber
--from Projects P
--left join EmployeeProject EP on P.projectID = EP.projectID
--group by P.projectID, P.projectName;

--3.
--select E.firstName, E.lastName
--from Employees E
--join EmployeeProject EP on EP.employeeID = E.employeeID
--join Employees M on E.managerID = M.employeeID
--join Departments D on E.departmentID = D.departmentID
--where M.departmentID = E.departmentID;

--4.
--select E.firstName as EmployeeFirstName,
--	   E.firstName as EmployeeLastName,
--	   M.firstName as ManagerFirstName,
--	   M.firstName as ManagerLastName
--from Employees E
--left join Employees M on E.managerID = M.employeeID;

--5.
--select EP.projectID,
--	   P.projectName,
--	count(distinct E.departmentID) as departmentCount
--from EmployeeProject EP
--join Projects P on EP.projectID = P.projectID
--join Employees E on EP.employeeID = E.employeeID
--group by EP.projectID, P.projectName
--having count(distinct E.departmentID) > 1;

--6.
--select concat(E.firstName , ' ' , E.lastName) as EmployeeName,
--	   D.departmentName as DepartmentName,
--	   EP.role as ProjectRole,
--	   P.projectName as ProjectName
--from Employees E
--left join Departments D on E.departmentID = D.departmentID
--left join EmployeeProject EP on E.employeeID = EP.employeeID
--left join Projects P on EP.projectID = P.projectID;

--7.
--select E.firstName , E.lastName
--from Employees E
--left join EmployeeProject EP on E.employeeID = EP.employeeID
--join Projects P on EP.projectID = P.projectID
--where P.projectName like '%Aplha%' or 
--	  P.projectName like '%Beta%';

--8.
--select concat(E.firstName, ' ', E.lastName) as EmployeeName,
--	   concat(M.firstName,' ' , M.lastName) as ManagerName,
--	   D.departmentName as DepartmentName,
--	   P.projectName,
--	   P.projectID,
--	   P.budget
--from Employees E
--join Employees M on M.employeeID = E.managerID
--left join Departments D on E.departmentID = D.departmentID
--left join EmployeeProject EP on E.employeeID = EP.employeeID
--left join Projects P on EP.projectID = P.projectID
--where M.employeeID = 101;

--9.
--select E.firstName, E.lastName, EP.role,
--	   P.projectName, P.projectID, P.budget
--from Employees E
--left join EmployeeProject EP on E.employeeID = EP.employeeID
--left join Projects P on EP.projectID = P.projectID;

--10.
--select E.firstName, 
--	   E.lastName, 
--	   E.employeeID,
--	   P.budget as ProjectBudget,
--	   avgDept.avgDeptProjectBudget
--from Employees E
--join EmployeeProject EP on E.employeeID = EP.employeeID
--join Projects P on EP.projectID = P.projectID
--join(
--	select departmentID, avg(budget) as avgDeptProjectBudget
--	from Projects
--	group by departmentID
--) avgDept on P.departmentID = avgDept.departmentID
--where P.budget > avgDept.avgDeptProjectBudget;

--SUBQUERIES

--1.
--select E.firstName, E.lastName
--from Employees E
--where E.salary > (
--	select avg(salary)
--	from Employees
--);

--2.
--select P.projectName,
--	   P.projectID,
--	   P.budget
--from Projects P
--where P.budget > (
--	select COALESCE(D.budget,0) ----so that it doesnt return NULL values
--	from Departments D
--	where D.departmentName = 'Marketing'
--);

--3.
--select E.firstName,
--	   E.lastName
--from Employees E
--where E.employeeID not in (
--	select EP.employeeID
--	from EmployeeProject EP
--);

--4.
--select D.departmentName, D.departmentID
--from Departments D
--where (
--	select count(E.employeeID)
--	from Employees E
--	where E.departmentID = d.departmentID
--) < (
--	select count(P.projectID)
--	from Projects P
--	where P.departmentID = D.departmentID
--);

--5.
--select E.firstName, E.lastName
--from Employees E
--where E.salary > (
--	select M.salary
--	from Employees M
--	where M.employeeID = E.managerID
--);

--6.
--select E.firstName, E.lastName, D.departmentName
--from Employees E
--join Departments D on D.departmentID = E.departmentID
--where E.salary > (
--	select avg(M.salary)
--	from Employees M
--	where M.departmentID = E.departmentID
--);

--7.
--select E.firstName, E.lastName, E.employeeID
--from Employees E
--join Departments D on E.departmentID = D.departmentID
--where D.budget > (
--	select avg(budget)
--	from Departments
--);

--8.
--select E.firstName, E.lastName, D.departmentName
--from Employees E
--join Departments D on E.departmentID = D.departmentID
--where E.employeeID not in(
--	select EP.employeeID
--	from EmployeeProject EP
--);

--9.
--select E.firstName, E.lastName, EP.role
--from Employees E
--left join EmployeeProject EP on E.employeeID = EP.employeeID
--where E.salary > (
--	select avg(M.salary)
--	from Employees M
--	join Departments D on M.departmentID = D.departmentID
--	where D.departmentName = 'Finance'
--);

--10.
--select E.firstName,
--	   E.lastName,
--	   E.employeeID
--from Employees E
--where E.hireDate > (
--	select max(M.hireDate)
--	from Employees M
--	where M.departmentID = E.departmentID
--	and M.salary = (
--		select max(M2.salary)
--		from Employees M2
--		where M2.departmentID = E.departmentID
--	)
--);


--SET OPERATIONS
--1.
--select E.firstName, E.lastName
--from Employees E
--where E.employeeID in (
--	select M.managerID
--	from Employees M
--	where M.managerID is not null
--)

--union 

--select E.firstName, E.lastName
--from Employees E
--where E.employeeID in (
--	select EP.employeeID
--	from EmployeeProject EP
--);

--2.
--select D.departmentID, D.departmentName
--from Departments D

--except

--select P.departmentID, null 
--from Projects P;

--3.
--select E.firstName, E.lastName
--from Employees E
--join EmployeeProject EP on E.employeeID = EP.employeeID
--join Projects P on EP.projectID = P.projectID
--where P.projectName = 'Project A'

--intersect

--select E.firstName, E.lastName
--from Employees E
--join EmployeeProject EP on E.employeeID = EP.employeeID
--join Projects P on EP.projectID = P.projectID
--where P.projectName = 'Project B';

--4.
--select E.firstName, E.lastName
--from Employees E
--join Departments D on E.departmentID = D.departmentID
--where D.departmentName = 'HR'

--union

--select E.firstName, E.lastName
--from Employees E
--join Departments D on E.departmentID = D.departmentID
--where D.departmentName = 'Finance';

--5.
--select P.projectName, P.projectID
--from Projects P

--EXCEPT

--select P.projectName, P.projectID
--from Projects P
--join EmployeeProject EP on P.projectID = EP.projectID
--where EP.employeeID = '101

--6.
--select E.firstName, E.lastName, E.employeeID,
--rank() over(
--	partition by E.departmentID
--	order by E.salary desc
--)
--from Employees E;

--7.
--select projectName, projectID, startDate,
-- sum(budget) over(order by startDate) as cumulative_budget
--from Projects;

--8.
--select employeeID, firstName, lastName, hireDate,
--	sum(salary) over(
--		order by hireDate
--	) as total_salary
--from Employees;

--9.
--select employeeID, firstName, lastName, hireDate,
--	rank() over(order by hireDate) as hire_rank
--from Employees;

--10.
--select firstName, lastName, employeeID, salary,
--	salary - avg(salary) over( partition by departmentID) as salary_diff
--from Employees;

--11.
--select employeeID, firstName, lastName, departmentID,
--	rank() over(partition by departmentID order by salary desc) as salary_rank
--from Employees;

--12.
--select *
--from (
--select employeeID, firstName, lastName,
--	row_number() over(order by salary desc) as rn
--from Employees
--) as RankSalary
--where rn <=5;

--13.
--select employeeID, firstName, lastName,
--	lead(salary) over(order by salary desc) as next_highest_salary,
--	salary - lead(salary) over(order by salary desc) as diff_salary 
--from Employees;

--14.
--select employeeID, firstName, lastName,
--lead(salary) over(partition by departmentID order by salary desc) as prev_sal,
--salary - lead(salary) over(partition by departmentID order by salary desc) as diff_prev_sal
--from Employees;

--15.
--select firstName, lastName, employeeID, 
--	DENSE_RANK() over(partition by departmentID order by salary desc) as dense_rank
--from Employees;


--REAL WORLD SCENARIOS
--1.
--select E.employeeID, E.firstName, E.lastName
--from Employees E
--where hireDate <= dateadd(year, -2, getdate()) 
--and E.employeeID in (
--	select E.employeeID
--	from EmployeeProject
--);


--2.
--select P.projectID, P.projectName, P.budget
--from Projects P
--where P.endDate is null
--and P.actualCost > P.budget * 1.10; --since actual cost is not in our data lets skip

--3.
--with AbsentDates as(
--	select employeeID, [date],
--	ROW_NUMBER() OVER (PARTITION BY employeeID ORDER BY [date]) 
--	- dense_rank() over (partition by employeeID, status order by [date]) as grp
--	from Attendance
--	where status = 'Absent'
--),
--GroupAbsent as (
--	select employeeID, count(*) as consecutive_days
--	from AbsentDates
--	group by employeeID, grp
--	having count(*) >= 3
--)
--select distinct employeeID
--from GroupAbsent;

--4.
--select distinct D.departmentID, D.departmentName
--from Employees E
--join Departments D on D.departmentID = E.departmentID
--join EmployeeProject EP on EP.employeeID = EP.employeeID
--join Projects P on EP.projectID = P.projectID
--where E.departmentID <> P.departmentID;


--5.
--select *
--from (
--select E.employeeID, E.firstName, E.lastName,
--	rank() over (partition by E.departmentID order by E.salary) as salary_rank
--from Employees E
--) ranked
--where salary_rank = 1;


--CTE QUESTIONS
--16.
--with myTable as(
--	select E.employeeID, E.firstName, E.lastName, D.departmentName
--	from Employees E
--	join Departments D on D.departmentID = E.departmentID
--)
--select * from myTable;


--17.
--with EmpH as (
--	select employeeID, firstName, lastName, managerID, 1 as level
--	from Employees
--	where managerID is null

--	union all

--	select E.employeeID, E.firstName, E.lastName, E.managerID,H.level+ 1 as level
--	from Employees E
--	join EmpH H on E.managerID = H.employeeID
--)

--select * from EmpH
--order by level, managerID;

--18.
--with Total_Salary_Exp as (
--	select D.departmentName,
--	sum(E.salary) as Total_salary
--	from Departments D
--	join Employees E on D.departmentID = E.departmentID
--	group by D.departmentName
--)
--select * from Total_Salary_Exp;

--19.
--with EmpProjCnt as (
--select E.employeeID, E.firstName, E.lastName, P.departmentID, count(*) as project_cnt
--from Employees E
--join EmployeeProject EP on E.employeeID = EP.employeeID
--join Projects P on P.projectID = EP.projectID
--group by E.employeeID, E.firstName, E.lastName, P.departmentID
--)
--select * from EmpProjCnt
--where project_cnt > 1;

--20.
--with SalaryHis as(
--	select E.employeeID, E.firstName, E.lastName, count(S.salary) as sall
--	from Employees E
--	join Salaries S on S.employeeID = E.employeeID
--	group by E.employeeID, E.firstName, E.lastName
--)

--select * from SalaryHis
--where sall>1;


--TRANSACTION
--1.
--begin TRANSACTION;

--UPDATE Employees
--SET Salary = Salary + 5000
--WHERE EmployeeID = 101;

--COMMIT;

--2.
--begin transaction;

--update Projects
--set departmentID = 3
--where projectID = 501;

--commit transaction;

--OR

--begin transaction;

--if exists (
--	select 1 from Projects
--	where projectID = 501 and departmentID <> 3
--)
--begin
--	update Projects
--	set departmentID = 3
--	where projectID = 501;

--	commit transaction;
--end
--else
--begin
--	print 'No update needed or project not found'
--	rollback transaction;
--end

--23.
--begin transaction;
--begin try
--	insert into EmployeeProject(employeeID, projectID, role)
--	values(105,301,'Tester')

--	commit;
--end try
--begin catch
--	rollback;
--	print 'MCG'
--end catch;

--24.
--begin transaction;

--delete from Departments
--where departmentID = 202;

--commit;

--25.
--begin transaction;

--insert into Salaries(employeeID,salary, startDate)
--values (105, 95000, getdate());

--insert into Attendance(employeeID, [date], status)
--values(105, getdate(), 'Present');

--commit;


--FORGEIN KEY CONSTRAINTS
--1.
--alter table Employees
--add constraint FK_Emp_Dep
--foreign key (departmentID)
--references Departments(departmentID);

--2.
--alter table Salaries
--add constraint uniq_sal_emp
--unique (employeeID, startDate); --if error is shoeing that means it is not unique

--3.
--alter table EmployeeProject
--add constraint fk_EP_P
--foreign key (projectID)
--references Projects(projectID);

--4.
--alter table Employees
--add constraint fk_dept
--foreign key (departmentID)
--references Departments(departmentID)
--on delete cascade;

--5.
--begin transaction

----step 1- ensure department exists
--if not exists(
--	select 1 from Departments where departmentID = 10
--)
--begin 
--	insert into Departments(departmentID, departmentName, budget)
--	values (10, 'Engineering', 100000);
--end

---- Step 2: Insert employee (assuming 105 is new)
--INSERT INTO Employees (employeeID, firstName, lastName, departmentID, salary, hireDate, status, managerID)
--VALUES (105, 'Mehak', 'Singh', 10, 90000, '2022-03-15', 'Active', NULL);

---- Step 3: Insert salary
--INSERT INTO Salaries (employeeID, salary, startDate)
--VALUES (105, 95000, GETDATE());

---- insert attendance
--INSERT INTO Attendance (employeeID, [date], status)
--VALUES (105, GETDATE(), 'Present');

--COMMIT;

--INDEXING
--1.
--create index departmentID
--on Employees(departmentID);

--2.
--create index idx_composite
--on EmployeeProject(projectID, employeeID);

--3.
--create index idx_emp_dept on Employees(departmentID);
--create index idx_emp_hireDate on Employees(hireDate);
--create index idx_emp_lastName on Employees(lastName);

--4.
--create index idx_emp_salary
--on Employees(salary);

--5.
-- identify slow queries(mysql)
--select top 10 *
--from sys.dm_exec_query_stats as qs
--cross apply sys.dm_exec_sql_text(qs.sql_handle)
--order by qs.total_elapsed_time desc;

--SHOW FULL PROCESSLIST;
--SHOW STATUS LIKE 'Slow_queries';

--server ke liye
SELECT TOP 10
    qs.total_elapsed_time / qs.execution_count AS avg_elapsed_time,
    qs.execution_count,
    qs.total_elapsed_time,
    SUBSTRING(qt.text, qs.statement_start_offset / 2 + 1,
              (CASE WHEN qs.statement_end_offset = -1 
                    THEN LEN(CONVERT(NVARCHAR(MAX), qt.text)) * 2 
                    ELSE qs.statement_end_offset END - qs.statement_start_offset) / 2) AS query_text
FROM sys.dm_exec_query_stats AS qs
CROSS APPLY sys.dm_exec_sql_text(qs.sql_handle) AS qt
ORDER BY avg_elapsed_time DESC;

































      function fit(x)
      common /pawpar/ par(3)
      fit=par(1)+par(2)*x**(0.5)+par(3)*x**(0.33)
      end

<script>
    // Add module
  $(document).ready(function(e){

      $('.vote').click(function(e){

      //inputs
      var $ticket_code         = $('#ticket_code');
      var $candidate         = $(this);


        if ( $ticket_code.val() == '') {

          swal("Ticket Code?", "Please enter your ticket Code..", "info");

        }

        else

        {


        swal({
            title: $.trim($candidate.text()),
            text: "is your vote?" ,
            type: 'info',
            confirmButtonColor: '#3085d6',
            cancelButtonColor: '#B3B3B3',
            showCancelButton: true,
            confirmButtonText: 'Yes',
            cancelButtonText: 'No',

          }

          ).then((result) => {

            if (result.value) {


              // json object
                var vote = {
                  ticket_code     : $ticket_code.val()  ,
                  candidate_id    : $candidate.attr('id'),
                  candidate_name      : $candidate.text() ,
                }

                    $.ajax({
                    type: 'POST',
                    url: '../includes/api/add_vote.php',
                    data: vote,
                    success: function(){;
                      swal(
                        $candidate.text(),
                        'Well done!, Wait for results.',
                        'success'
                      )
                    },

                    error: function(){
                      swal("One vote, One ticket", "You have already voted!");
                    }

                  });
            }
          })

        }

    });
});

</script>

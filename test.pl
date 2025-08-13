#!/usr/bin/perl

use strict;
use warnings;
use Getopt::Long;

my $BSQ_EXECUTABLE = './bsq';
my $MAPS_DIRECTORY = './maps';
my $LEAK_CHECKER_CMD;
my $LEAK_CHECKER_NAME;

if ($^O eq 'darwin') {
    $LEAK_CHECKER_CMD   = "leaks -atExit --";
    $LEAK_CHECKER_NAME  = "leaks";
} else {
    $LEAK_CHECKER_CMD   = 'valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1';
    $LEAK_CHECKER_NAME  = "valgrind";
}

my $COLOR_GREEN   = "\033[32m";
my $COLOR_RED     = "\033[31m";
my $COLOR_YELLOW  = "\033[33m";
my $COLOR_RESET   = "\033[0m";

sub main {
    my $run_leak_check = 0;
    GetOptions('leaks' => \$run_leak_check) or die "Error in command line arguments.\n";

    unless (-x $BSQ_EXECUTABLE) {
        die "Error: Cannot find or execute '$BSQ_EXECUTABLE'. Please compile your project first with 'make'.\n";
    }

    my $has_leak_checker = 0;
    if ($^O eq 'darwin') {
        $has_leak_checker = (system("which leaks >/dev/null 2>&1") == 0);
    } else {
        $has_leak_checker = (system("which valgrind >/dev/null 2>&1") == 0);
    }

    print "Starting BSQ test...\n";
    if ($run_leak_check && !$has_leak_checker) {
        print $COLOR_YELLOW . "Warning: $LEAK_CHECKER_NAME not found. Cannot perform memory leak checks.\n" . $COLOR_RESET;
    } elsif (!$run_leak_check) {
        print "Hint: Use the --leaks flag to enable memory checks.\n";
    }

    my @map_files = get_map_files($MAPS_DIRECTORY);
    if (!@map_files) {
        die "Error: No map files found in '$MAPS_DIRECTORY'.\n";
    }

    my $passed_count = 0;
    my $leaked_count = 0;

    foreach my $map_file (@map_files) {
        my $full_path = "$MAPS_DIRECTORY/$map_file";

        my $c_output = `$BSQ_EXECUTABLE $full_path`;
        my $perl_output = solve_bsq_in_perl($full_path);
        my $is_correct = ($c_output eq $perl_output);

        if ($is_correct) {
            print $COLOR_GREEN . "[  OK  ]" . $COLOR_RESET;
            $passed_count++;
        } else {
            print $COLOR_RED . "[ FAIL ]" . $COLOR_RESET;
        }

        if ($run_leak_check && $has_leak_checker) {
            if ($^O eq 'darwin') {
                my $tmp_file = ".leaks.tmp";
                system("$LEAK_CHECKER_CMD $BSQ_EXECUTABLE $full_path > $tmp_file 2>&1");
                my $leaks_output = "";
                if (open(my $fh, '<', $tmp_file)) {
                    $leaks_output = do { local $/; <$fh> };
                    close($fh);
                }
                unlink($tmp_file);

                if ($leaks_output =~ /0 leaks for 0 total leaked bytes/) {
                     print " " . $COLOR_GREEN . "[MEM OK]" . $COLOR_RESET;
                } else {
                     print " " . $COLOR_RED . "[LEAK!]" . $COLOR_RESET;
                     $leaked_count++;
                }
            } else {
                system("$LEAK_CHECKER_CMD $BSQ_EXECUTABLE $full_path >/dev/null 2>&1");
                if ($? == 0) {
                    print " " . $COLOR_GREEN . "[MEM OK]" . $COLOR_RESET;
                } else {
                    print " " . $COLOR_RED . "[LEAK!]" . $COLOR_RESET;
                    $leaked_count++;
                }
            }
        }

        print ": $map_file\n";
    }

    my $total_tests = @map_files;
    my $failed_count = $total_tests - $passed_count;
    print "\n--- Test Summary ---\n";
    print "Correctness: " . $COLOR_GREEN . "$passed_count/$total_tests passed." . $COLOR_RESET;
    if ($failed_count > 0) {
        print " " . $COLOR_RED . "($failed_count failed)" . $COLOR_RESET;
    }
    print "\n";
    if ($run_leak_check && $has_leak_checker) {
        print "Memory Leaks: " . $COLOR_RED . "$leaked_count/$total_tests leaked." . $COLOR_RESET . "\n";
    }
}

sub get_map_files {
    my ($dir) = @_;
    opendir(my $dh, $dir) or die "Can't open directory '$dir': $!";
    my @files = sort {
        my ($a_num) = $a =~ /^(\d+)/;
        my ($b_num) = $b =~ /^(\d+)/;
        $a_num <=> $b_num;
    } grep { !/^\./ } readdir($dh);
    closedir $dh;
    return @files;
}

sub solve_bsq_in_perl {
    my ($filepath) = @_;
    open(my $fh, '<', $filepath) or return "map error\n";

    my $first_line = <$fh>;
    chomp $first_line;
    unless ($first_line =~ /^(\d+)(.)(.)(.)$/) {
        close $fh;
        return "map error\n";
    }
    my ($height, $empty, $obstacle, $full) = ($1, $2, $3, $4);
    if ($height <= 0 || $empty eq $obstacle || $empty eq $full || $obstacle eq $full) {
        return "map error\n";
    }

    my @grid;
    my $width = -1;
    for (1 .. $height) {
        my $line = <$fh>;
        return "map error\n" unless defined $line;
        chomp $line;
        if ($width == -1) { $width = length($line); }
        return "map error\n" if length($line) != $width;
        return "map error\n" if $line =~ /[^$empty$obstacle]/;
        push @grid, $line;
    }

    return "map error\n" if defined <$fh>;
    close $fh;

    my @cache;
    my $max_size = 0;
    my ($sol_r, $sol_c) = (0, 0);

    for my $r (0 .. $height - 1) {
        for my $c (0 .. $width - 1) {
            if (substr($grid[$r], $c, 1) eq $obstacle) {
                $cache[$r][$c] = 0;
            } else {
                if ($r == 0 || $c == 0) {
                    $cache[$r][$c] = 1;
                } else {
                    my $min = $cache[$r-1][$c];
                    $min = $cache[$r][$c - 1] if $cache[$r][$c - 1] < $min;
                    $min = $cache[$r - 1][$c - 1] if $cache[$r - 1][$c - 1] < $min;
                    $cache[$r][$c] = 1 + $min;
                }
            }
            if ($cache[$r][$c] > $max_size) {
                $max_size = $cache[$r][$c];
                $sol_r = $r;
                $sol_c = $c;
            }
        }
    }

    if ($max_size > 0) {
        my $start_r = $sol_r - $max_size + 1;
        my $start_c = $sol_c - $max_size + 1;
        for my $r ($start_r .. $sol_r) {
            for my $c ($start_c .. $sol_c) {
                substr($grid[$r], $c, 1) = $full;
            }
        }
    }

    return join("\n", @grid) . "\n";
}

main();
